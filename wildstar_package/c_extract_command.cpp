#include "c_extract_command.h"

#include <iostream>
#include <iomanip>

#include <QDebug>

#include "wildstar/data/c_archive.h"

using wildstar::data::CArchive;

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
          , source( "" )
          ;

    if( args.size() == 4 )
    {
        source = args.at( 2 );
    }

    CArchive file( filename );
    file.open();

    bool extract_block( false );
    uint block_index( source.toUInt( &extract_block ) );
    qDebug() << "src: " << source
             << "dst: " << destination
             << "block_index: " << block_index
             << "extract_block: " << extract_block
             ;

    if( extract_block )
    {
        QFile out( destination );
        out.open( QIODevice::WriteOnly ); // | QIODevice::Truncate
        file.extractBlock( block_index, out );
        out.close();
    }

    return 0;
}

//------------------------------------------------------------------------------
