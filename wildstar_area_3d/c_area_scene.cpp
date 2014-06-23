#include "c_area_scene.h"
#include "camera.h"

#include <string.h>

#include <QImage>
#include <QGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions_4_0_Core>

#define _USE_MATH_DEFINES
#include <math.h>

using wildstar::data::area::CChunk;

//------------------------------------------------------------------------------
const float degToRad = float( M_PI / 180.0 );

//------------------------------------------------------------------------------
CAreaScene::CAreaScene(const wildstar::data::area::CArea* area, QObject* parent )
    : AbstractScene( parent ),
      m_camera( new Camera( this ) ),
      m_v(),
      m_viewCenterFixed( false ),
      m_panAngle( 0.0f ),
      m_tiltAngle( 0.0f ),
      m_patchBuffer( QOpenGLBuffer::VertexBuffer ),
      m_screenSpaceError( 12.0f ),
      m_modelMatrix(),
      m_horizontalScale( 2.0f * 16.0f ),
      m_verticalScale( 1.0f / 8.0f ),
      m_sunTheta( 30.0f ),
      m_time( 0.0f ),
      m_metersToUnits( 0.5f ), // 500 units == 10 km => 0.05 units/m
      m_displayMode( SimpleWireFrame ),
      m_displayModeSubroutines( DisplayModeCount ),
      m_funcs( 0 ),
      area_(area)
{
    m_modelMatrix.setToIdentity();

    // Initialize the camera position and orientation
    const float height( 1132.0 );
    m_camera->setPosition( QVector3D( 0.0f, height, 0.0f ) );
    m_camera->setViewCenter( QVector3D( 1.0f, height, 1.0f ) );
    m_camera->setUpVector( QVector3D( 0.0f, 1.0f, 0.0f ) );

    m_displayModeNames << QStringLiteral( "shaderSimpleWireFrame" )
                       << QStringLiteral( "shadeWorldHeight" )
                       << QStringLiteral( "shadeWorldNormal")
                       << QStringLiteral( "shadeGrass" )
                       << QStringLiteral( "shadeGrassAndRocks" )
                       << QStringLiteral( "shadeGrassRocksAndSnow" )
                       << QStringLiteral( "shadeLightingFactors" )
                       << QStringLiteral( "shadeTexturedAndLit" );
}

//------------------------------------------------------------------------------
void
CAreaScene::initialise()
{
    m_funcs = m_context->versionFunctions<QOpenGLFunctions_4_0_Core>();
    if ( !m_funcs )
    {
        qFatal("Requires OpenGL >= 4.0");
        exit( 1 );
    }
    m_funcs->initializeOpenGLFunctions();

    // Initialize resources
    prepareShaders();
    prepareTextures();
    prepareVertexBuffers( m_heightMapSize );
    prepareVertexArrayObject();

    // Enable depth testing
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );

    glClearColor( 0.65f, 0.77f, 1.0f, 1.0f );

    // Set the wireframe line properties
    QOpenGLShaderProgramPtr shader = m_material->shader();
    shader->bind();
    shader->setUniformValue( "line.width", 1.0f );
    shader->setUniformValue( "line.color", QVector4D( 0.0f, 1.0f, 0.0f, 1.0f ) );

    // Set the fog parameters
    shader->setUniformValue( "fog.color", QVector4D( 0.65f, 0.77f, 1.0f, 1.0f ) );
    shader->setUniformValue( "fog.minDistance", 4096.0f );
    shader->setUniformValue( "fog.maxDistance", 10240.0f );

    // Get subroutine indices
    for ( int i = 0; i < DisplayModeCount; ++i)
    {
        m_displayModeSubroutines[i] =
            m_funcs->glGetSubroutineIndex( shader->programId(),
                                           GL_FRAGMENT_SHADER,
                                           m_displayModeNames.at( i ).toLatin1() );
    }
}

//------------------------------------------------------------------------------
void
CAreaScene::update( float t )
{
    m_modelMatrix.setToIdentity();

    // Store the time
    const float dt = t - m_time;
    m_time = t;

    // Update the camera position and orientation
    Camera::CameraTranslationOption option = m_viewCenterFixed
                                           ? Camera::DontTranslateViewCenter
                                           : Camera::TranslateViewCenter;
    m_camera->translate( m_v * dt * m_metersToUnits, option );

    if ( !qFuzzyIsNull( m_panAngle ) )
    {
        m_camera->pan( m_panAngle, QVector3D( 0.0f, 1.0f, 0.0f ) );
        m_panAngle = 0.0f;
    }

    if ( !qFuzzyIsNull( m_tiltAngle ) )
    {
        m_camera->tilt( m_tiltAngle );
        m_tiltAngle = 0.0f;
    }
}

//------------------------------------------------------------------------------
void
CAreaScene::render()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_material->bind();
    QOpenGLShaderProgramPtr shader = m_material->shader();
    shader->bind();

    // Set the fragment shader display mode subroutine
    m_funcs->glUniformSubroutinesuiv( GL_FRAGMENT_SHADER, 1,
                                      &m_displayModeSubroutines[m_displayMode] );

    // Set the horizontal and vertical scales applied in the tess eval shader
    shader->setUniformValue( "horizontalScale", m_horizontalScale );
    shader->setUniformValue( "verticalScale", m_verticalScale );
    shader->setUniformValue( "pixelsPerTriangleEdge", m_screenSpaceError );

    // Pass in the usual transformation matrices
    QMatrix4x4 viewMatrix = m_camera->viewMatrix();
    QMatrix4x4 modelViewMatrix = viewMatrix * m_modelMatrix;
    QMatrix3x3 worldNormalMatrix = m_modelMatrix.normalMatrix();
    QMatrix3x3 normalMatrix = modelViewMatrix.normalMatrix();
    QMatrix4x4 mvp = m_camera->projectionMatrix() * modelViewMatrix;
    shader->setUniformValue( "modelMatrix", m_modelMatrix );
    shader->setUniformValue( "modelViewMatrix", modelViewMatrix );
    shader->setUniformValue( "worldNormalMatrix", worldNormalMatrix );
    shader->setUniformValue( "normalMatrix", normalMatrix );
    shader->setUniformValue( "mvp", mvp );

    // Set the lighting parameters
    QVector4D worldLightDirection( sinf( m_sunTheta * degToRad ), cosf( m_sunTheta * degToRad ), 0.0f, 0.0f );
    QMatrix4x4 worldToEyeNormal( normalMatrix );
    QVector4D lightDirection = worldToEyeNormal * worldLightDirection;
    shader->setUniformValue( "light.position", lightDirection );
    shader->setUniformValue( "light.intensity", QVector3D( 1.0f, 1.0f, 1.0f ) );

    // Set the material properties
    shader->setUniformValue( "material.Ka", QVector3D( 0.1f, 0.1f, 0.1f ) );
    shader->setUniformValue( "material.Kd", QVector3D( 1.0f, 1.0f, 1.0f ) );
    shader->setUniformValue( "material.Ks", QVector3D( 0.3f, 0.3f, 0.3f ) );
    shader->setUniformValue( "material.shininess", 10.0f );

    // Render the quad as a patch
    {
        QOpenGLVertexArrayObject::Binder binder( &m_vao );
        shader->setPatchVertexCount( 1 );
        glDrawArrays( GL_PATCHES, 0, m_patchCount );
    }
}

//------------------------------------------------------------------------------
void
CAreaScene::resize( int w, int h )
{
    // Make sure the viewport covers the entire window
    glViewport( 0, 0, w, h );

    m_viewportSize = QVector2D( float( w ), float( h ) );

    // Update the projection matrix
    float aspect = static_cast<float>( w ) / static_cast<float>( h );
    m_camera->setPerspectiveProjection( 25.0f, aspect, 0.1f, 10240.0f );

    // Update the viewport matrix
    float w2 = w / 2.0f;
    float h2 = h / 2.0f;
    m_viewportMatrix.setToIdentity();
    m_viewportMatrix.setColumn( 0, QVector4D( w2, 0.0f, 0.0f, 0.0f ) );
    m_viewportMatrix.setColumn( 1, QVector4D( 0.0f, h2, 0.0f, 0.0f ) );
    m_viewportMatrix.setColumn( 2, QVector4D( 0.0f, 0.0f, 1.0f, 0.0f ) );
    m_viewportMatrix.setColumn( 3, QVector4D( w2, h2, 0.0f, 1.0f ) );

    // We need the viewport size to calculate tessellation levels
    QOpenGLShaderProgramPtr shader = m_material->shader();
    shader->setUniformValue( "viewportSize", m_viewportSize );

    // The geometry shader also needs the viewport matrix
    shader->setUniformValue( "viewportMatrix", m_viewportMatrix );
}

//------------------------------------------------------------------------------
void
CAreaScene::prepareShaders()
{
    m_material = MaterialPtr( new Material );
    m_material->setShaders( ":/shaders/terraintessellation.vert",
                            ":/shaders/terraintessellation.tcs",
                            ":/shaders/terraintessellation.tes",
                            ":/shaders/terraintessellation.geom",
                            ":/shaders/terraintessellation.frag" );
}

//------------------------------------------------------------------------------
void
CAreaScene::prepareTextures()
{
    SamplerPtr sampler( new Sampler );
    sampler->create();
    sampler->setMinificationFilter( GL_LINEAR );
    sampler->setMagnificationFilter( GL_LINEAR );
    sampler->setWrapMode( Sampler::DirectionS, GL_CLAMP_TO_EDGE );
    sampler->setWrapMode( Sampler::DirectionT, GL_CLAMP_TO_EDGE );

    m_funcs->glActiveTexture( GL_TEXTURE0 );
    TexturePtr height_map( new QOpenGLTexture( QOpenGLTexture::Target2DArray ) );
    height_map->setAutoMipMapGenerationEnabled( false );
    height_map->setFormat( QOpenGLTexture::R16I );
    int width( 18 ), height( width );
    height_map->setSize( width, height );
    height_map->setLayers( area_->chunks().count() );
    height_map->allocateStorage();
    int layer(0);
    foreach( const CChunk& chunk, area_->chunks() )
    {
        qint16 data[height][width];
        for( int y = 0; y < height; ++y )
        {
            for( int x = 0; x < width; ++x )
            {
                int idx = y * 19 + x;
                data[y][x] = chunk.height_map[idx];
            }
        }
        height_map->setData( 0, layer++, QOpenGLTexture::Red_Integer, QOpenGLTexture::Int16, data );
    }
    m_heightMapSize.setHeight( 16 );
    m_heightMapSize.setWidth( 16 );
    m_material->setTextureUnitConfiguration( 0, height_map, sampler, QByteArrayLiteral( "heightMap" ) );

    m_funcs->glActiveTexture( GL_TEXTURE0 );

    SamplerPtr compass_sampler( new Sampler );
    compass_sampler->create();
    compass_sampler->setMinificationFilter( GL_LINEAR_MIPMAP_LINEAR );
    m_funcs->glSamplerParameterf( compass_sampler->samplerId(), GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f );
    compass_sampler->setMagnificationFilter( GL_LINEAR );
    compass_sampler->setWrapMode( Sampler::DirectionS, GL_REPEAT );
    compass_sampler->setWrapMode( Sampler::DirectionT, GL_REPEAT );

    QImage compass_image( "Western.3c3d.tex.bmp" );
    m_funcs->glActiveTexture( GL_TEXTURE1 );
    TexturePtr compass( new QOpenGLTexture( compass_image ) );
    m_material->setTextureUnitConfiguration( 1, compass, compass_sampler, QByteArrayLiteral( "compassTexture" ) );

    SamplerPtr tiling_sampler( new Sampler );
    tiling_sampler->create();
    tiling_sampler->setMinificationFilter( GL_LINEAR_MIPMAP_LINEAR );
    m_funcs->glSamplerParameterf( tiling_sampler->samplerId(), GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f );
    tiling_sampler->setMagnificationFilter( GL_LINEAR );
    tiling_sampler->setWrapMode( Sampler::DirectionS, GL_REPEAT );
    tiling_sampler->setWrapMode( Sampler::DirectionT, GL_REPEAT );

    /*
    m_funcs->glActiveTexture( GL_TEXTURE2 );
    TexturePtr terrain( new QOpenGLTexture( QOpenGLTexture::Target2DArray ) );
    terrain->setAutoMipMapGenerationEnabled( false );
    terrain->setFormat( QOpenGLTexture::R16I );
    terrain->setSize( 1024, 1024 );
    terrain->setLayers( area_->chunks().count() );
    terrain->allocateStorage();
    int layer(0);
    m_material->setTextureUnitConfiguration( 1, compass, compass_sampler, QByteArrayLiteral( "terrainTexture" ) );
    */

    m_funcs->glActiveTexture( GL_TEXTURE0 );
}

//------------------------------------------------------------------------------
void
CAreaScene::prepareVertexBuffers( QSize heightMapSize )
{
    m_patchCount = area_->chunks().count();
    QVector<float> positionData( 2 * m_patchCount ); // 2 floats per vertex
    qDebug() << "Total number of patches =" << m_patchCount;

    for ( int y = 0; y < heightMapSize.height(); ++y ) {
        for ( int x = 0; x < heightMapSize.width(); ++x ) {
            int i = y * heightMapSize.width() + x;
            positionData[i*2+0] = x * 1.0;
            positionData[i*2+1] = y * 1.0;
        }
    }
    m_patchBuffer.create();
    m_patchBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
    m_patchBuffer.bind();
    m_patchBuffer.allocate( positionData.data(), positionData.size() * sizeof( float ) );
    m_patchBuffer.release();
}

//------------------------------------------------------------------------------
void
CAreaScene::prepareVertexArrayObject()
{
    // Create a VAO for this "object"
    m_vao.create();
    {
        QOpenGLVertexArrayObject::Binder binder( &m_vao );
        QOpenGLShaderProgramPtr shader = m_material->shader();
        shader->bind();
        m_patchBuffer.bind();
        shader->enableAttributeArray( "vertexPosition" );
        shader->setAttributeBuffer( "vertexPosition", GL_FLOAT, 0, 2 );
    }
}

//------------------------------------------------------------------------------
