#include "c_area_widget.h"

#include <QtWidgets>
#include <QtOpenGL>

#include <math.h>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

using wildstar::data::area::CArea;
using wildstar::data::area::CChunk;
using wildstar::data::CArray;

//------------------------------------------------------------------------------
CAreaWidget::CAreaWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
    xPos = 0;
    zPos = -4096;
    area_ = NULL;
}

//------------------------------------------------------------------------------
CAreaWidget::~CAreaWidget()
{
}

//------------------------------------------------------------------------------
QSize
CAreaWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

//------------------------------------------------------------------------------
QSize
CAreaWidget::sizeHint() const
{
    return QSize(400, 400);
}

//------------------------------------------------------------------------------
void
CAreaWidget::setArea( const wildstar::data::area::CArea* area )
{
    area_ = area;
}

//------------------------------------------------------------------------------
static void
qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

//------------------------------------------------------------------------------
void
CAreaWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

//------------------------------------------------------------------------------
void
CAreaWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

//------------------------------------------------------------------------------
void
CAreaWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

//------------------------------------------------------------------------------
void
CAreaWidget::initializeGL()
{
    //qglClearColor(QColor::);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

//------------------------------------------------------------------------------
void
CAreaWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    glTranslatef( xPos / 16.0, 0.0, zPos / 16.0 );

    if( area_ == NULL ) return;

    const CArea::ChunkList& chunks( area_->chunks() );

    int rows( 19 ), cols( rows );
    glBegin(GL_POINTS);
    GLfloat tile_step( 8.0 )
          , tile_z( tile_step * -8.0 )
          , chunk_step( 0.5 )
          , y_scale( 1.0 / 32.0 )
          ;
    for( int tile_row(0); tile_row < 16; ++tile_row, tile_z += tile_step )
    {
        GLfloat tile_x(  tile_step * -8.0 );
        for( int tile_col(0); tile_col < 16; ++tile_col, tile_x += tile_step )
        {
            GLfloat z( tile_z );
            const CArray<quint16,19*19>& height_map( chunks[16*tile_row + tile_col].height_map );
            for ( int row(0); row < rows; ++row, z += chunk_step )
            {
                GLfloat x( tile_x );
                for ( int col(0); col< cols; ++col, x += chunk_step )
                {
                    quint16 height( height_map[(row + 0 )*cols + ( col + 0 ) ] );
                    GLfloat y1( height );
                    //GLfloat y2( height_map[(row + 0 )*65 + ( col + 1 ) ] );
                    //GLfloat y3( height_map[(row + 1 )*65 + ( col + 1 ) ] );
                    //GLfloat y4( height_map[(row + 1 )*65 + ( col + 0 ) ] );
                    y1 = -300.0 + y1 * y_scale;
                    //y2 = y2 / y_scale;
                    //y3 = y3 / y_scale;
                    //y4 = y4 / y_scale;
                    glVertex3f( x             , y1, z );
                    //glVertex3f( x             , y2, z + chunk_step );
                    //glVertex3f( x + chunk_step, y3, z + chunk_step );
                    //glVertex3f( x + chunk_step, y4, z );
                }
            }
        }
    }
    glEnd();
}

//------------------------------------------------------------------------------
void
CAreaWidget::resizeGL( int width, int height )
{
    glViewport( 0, 0, width, height );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLdouble xmin, xmax, ymin, ymax
      , zNear(1.0)
      , zFar(4096.0)
      , aspect( width )
      ;
    aspect /= height;
    ymax = zNear * tan( 90 * M_PI / 360.0 );
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;

    glFrustum( xmin, xmax, ymin, ymax, zNear, zFar );

    glMatrixMode(GL_MODELVIEW);
}

//------------------------------------------------------------------------------
void
CAreaWidget::mousePressEvent( QMouseEvent *event )
{
    lastPos = event->pos();
}

//------------------------------------------------------------------------------
void
CAreaWidget::mouseMoveEvent( QMouseEvent *event )
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        xPos += 8 * dx;
        zPos += 8 * dy;
        updateGL();
    }
    lastPos = event->pos();
}

//------------------------------------------------------------------------------
