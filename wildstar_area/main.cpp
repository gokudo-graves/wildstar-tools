#include <QDebug>

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDataStream>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QImage>

#include "wildstar/data/area/c_area.h"

using wildstar::data::area::CArea;
using wildstar::data::area::CChunk;

int main( int argc, char *argv[] )
{
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    //parser.setApplicationDescription( app.translate("main", "tool to do some basic actions on wildstar data files") );
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("area-file", app.translate("main", "the wildstar area file to work on"), "*.area");
    parser.process( app );
    const QStringList args( parser.positionalArguments() );

    if( args.size() != 1 )
    {
        parser.showHelp( 1 );
    }

    try
    {
        QString area_path( args.front() );
        QFile file( area_path );
        file.open( QIODevice::ReadOnly );

        QDataStream stream( &file );
        stream.setByteOrder( QDataStream::LittleEndian );

        CArea area;
        stream >> area;
        int chunk_width(19), chunk_height(chunk_width);

        QImage image( 16*chunk_width, 16*chunk_height, QImage::Format_RGB32 );

        for( int iy(0); iy < 16; ++iy )
        {
            for( int ix(0); ix < 16; ++ix )
            {
                int chunk_index( iy * 16 + ix );
                const CChunk& chunk( area.chunks().at( chunk_index ) );
                for( int cy(0); cy < chunk_height; ++cy )
                {
                    for( int cx(0); cx < chunk_width; ++cx )
                    {
                        int x( ix * chunk_width  + cx )
                          , y( iy * chunk_height + cy )
                          ;
                        quint16 height( chunk.heigh_map [cy*chunk_height+cx] );
                        uint color( 0 );
                        color |= (height & 0x001F) << 3;
                        color |= (height & 0x07E0) << 5;
                        color |= (height & 0xF800) << 8;
                        color = height;
                        image.setPixel( x, y, color );
                    }
                }
            }
        }

        QFileInfo area_info( area_path );
        QString image_name( area_info.completeBaseName() + ".png" );
        image.save( area_info.dir().filePath( image_name ) );

        return 0;
    }
    catch ( std::exception& e )
    {
        qDebug() << "Exception: " << e.what();
    }

    return 1;
}
