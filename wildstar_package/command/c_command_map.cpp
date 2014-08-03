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
CCommandMap::get( QCommandLineParser& parser ) const
{
    ICommand* command( get( parser, parser.positionalArguments() ) );
    parser.clearPositionalArguments();
    return command;
}

//------------------------------------------------------------------------------
ICommand*
CCommandMap::get( QCommandLineParser& parser, const QStringList args ) const
{
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
void
CCommandMap::add(ICommand* command)
{
    insert( command->name(), command );
}

//------------------------------------------------------------------------------

}
