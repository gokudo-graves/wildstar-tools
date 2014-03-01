#include "c_extract_command.h"

#include <iostream>
#include <iomanip>

#include <QDir>

#include <QDebug>

#include "wildstar/data/c_archive.h"
#include "wildstar/data/c_archive_index.h"

using wildstar::data::CArchive;
using wildstar::data::CArchiveIndex;

//------------------------------------------------------------------------------
CExtractCommand::CExtractCommand()
{
}

//------------------------------------------------------------------------------
void
CExtractCommand::options( QCommandLineParser& parser ) const
{
    parser.addPositionalArgument("extract", "application-parameter-command-list", "extract");
    parser.addPositionalArgument("archive-file", "application-parameter-archive-file", "*.archive");
    parser.addPositionalArgument("source", "application-parameter-source", "[0..n|filepath]");
    parser.addPositionalArgument("destination", "application-parameter-destination");
}

//------------------------------------------------------------------------------
int
CExtractCommand::execute( QCommandLineParser& parser )
{
    const QStringList args( parser.positionalArguments() );

    if( args.size() < 3 || args.size() > 4 )
    {
        parser.showHelp( 1 );
    }
    QString filename( args.at( 1 ) )
          , destination( args.back() )
          , source( args.size() > 2 ? args.at( 2 ) : "" )
          ;

    archive_.open( filename );

    ExtractMode mode( UNKNOWN );
    bool is_source_int( false );
    uint block_index( source.toUInt( &is_source_int ) );
    if( is_source_int )
    {
        mode = BLOCK;
    }
    else
    {
        mode = FILE;
    }

    QFileInfo   file_info( filename );
    QString     index_filename( file_info.path() + "/" + file_info.completeBaseName() + ".index" );
    switch ( mode ) {
        case FILE:
            qDebug() << "\narchive : " << filename
                     << "\nindex   : " << index_filename
                     ;
            break;

        case BLOCK:
            extractBlock( block_index, destination );
            break;

        case UNKNOWN:
        default:
            parser.showHelp( 1 );
    }

    return 0;
}

//------------------------------------------------------------------------------
void
CExtractCommand::extractBlock(const uint block, const QString& destination )
{
    QString     out_file_path( destination );
    QFileInfo   out_info( destination );
    if( out_info.fileName().isEmpty() )
    {
        QDir::current().mkpath( out_info.path() );
        QString file_name( QString( "block.%1.bin").arg( block ) );
        out_file_path = out_info.dir().filePath( file_name );
    }
    QFile out( out_file_path );
    out.open( QIODevice::WriteOnly );
    archive_.extractBlock( block, out );
    out.close();
}

//------------------------------------------------------------------------------
