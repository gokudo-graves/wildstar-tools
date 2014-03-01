#include "c_extract_command.h"

#include <iostream>
#include <iomanip>

#include <QDir>

#include <QDebug>

#include "wildstar/data/c_archive.h"
#include "wildstar/data/c_archive_index.h"

using wildstar::data::CArchive;
using wildstar::data::CArchiveIndex;
using wildstar::data::CIndexFileNode;

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
    QString archive_file_path( args.at( 1 ) )
          , destination( args.back() )
          , source( args.size() > 2 ? args.at( 2 ) : "" )
          ;

    archive_.open( archive_file_path );

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
        QFileInfo   source_info( source );
        if( source_info.fileName().isEmpty() )
        {
            mode = DIRECTORY;
        }
    }

    QFileInfo   file_info( archive_file_path );
    QString     index_file_name( file_info.completeBaseName() + ".index" );
    QString     index_file_path( file_info.dir().filePath( index_file_name ) );
    const CIndexFileNode* file_node( NULL );

    switch ( mode ) {
        case FILE:
            qDebug() << "\narchive : " << archive_file_path
                     << "\nindex   : " << index_file_path
                     << "\nsrc     : " << source
                     << "\ndst     : " << destination
                     ;
            index_.open( index_file_path );
            file_node = index_.file( source );
            if( file_node == NULL )
            {
                std::cout << qPrintable(source) << ": File not found in index.\n";
                return 1;
            }
            if( !archive_.contains( file_node->hash() ) )
            {
                std::cout << qPrintable(file_node->hash().toHex() ) << ": File hash not found in archive.\n";
                return 1;
            }
            extractFile( file_node, destination );
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
CExtractCommand::extractBlock( const uint block, const QString& destination, QString file_name )
{
    if( file_name.isEmpty() )
    {
        file_name = QString( "block.%1.bin").arg( block );
    }

    QDir::current().mkpath( destination );
    QDir        out_path( destination );
    QString     out_file_path( out_path.filePath( file_name ) );
    QFile       out( out_file_path );
    out.open( QIODevice::WriteOnly );
    archive_.writeBlock( block, out );
    out.close();
}

//------------------------------------------------------------------------------
void
CExtractCommand::extractFile( const wildstar::data::CIndexFileNode* file_node, const QString& destination )
{
    const CArchive::File& file( archive_.file( file_node->hash() )  );
    extractBlock( file.block_index, destination, file_node->name() );
}

//------------------------------------------------------------------------------
