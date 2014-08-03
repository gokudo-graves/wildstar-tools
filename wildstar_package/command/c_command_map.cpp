#include "c_command_map.h"

namespace command {

//------------------------------------------------------------------------------
CCommandMap::CCommandMap()
{
}

//------------------------------------------------------------------------------
CCommandMap::~CCommandMap()
{
    foreach ( ICommand* command, values() ) {
        delete command;
    }
}

//------------------------------------------------------------------------------
void
CCommandMap::options( QCommandLineParser& parser ) const
{
    const QString command_list( QStringList( keys() ).join( "|" ) );
    parser.addPositionalArgument( "command", "the command to execute, use <command> --help for detailed information", command_list );
}

//------------------------------------------------------------------------------
ICommand*
CCommandMap::find( QCommandLineParser& parser ) const
{
    const QStringList args( parser.positionalArguments() );
    if( args.isEmpty() )
    {
        parser.showHelp( 1 );
    }

    const_iterator it_command( find( args.first() ) );
    if( it_command == end() )
    {
        parser.showHelp( 1 );
    }

    return it_command.value();
}

//------------------------------------------------------------------------------

}
