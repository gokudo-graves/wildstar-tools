#include "c_extract_command.h"

#include <iostream>
#include <iomanip>

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
}

//------------------------------------------------------------------------------
int
CExtractCommand::execute( QCommandLineParser& parser )
{
    const QStringList args( parser.positionalArguments() );

    if( args.size() != 2 )
    {
        parser.showHelp( 1 );
    }
    QString filename( args.at( 1 ) );
    CArchive file( filename );

    file.open();
    return 0;
}

//------------------------------------------------------------------------------
