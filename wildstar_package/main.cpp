#include <QDebug>

#include <QCommandLineOption>
#include <QCoreApplication>

#include "command/c_extract.h"
#include "command/c_list.h"

typedef QMap<QString, command::ICommand*>    CommandMap;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationVersion( "0.0.1" );

    QCommandLineParser parser;
    parser.setApplicationDescription( app.translate("main", "tool to do some basic actions on wildstar data files") );
    parser.addHelpOption();
    parser.addVersionOption();

    const QCommandLineOption    OPTION_INI_FILE(QStringList() << "i" << "ini-file", "ini file with settings to use", "wildstar.ini");
    parser.addOption( OPTION_INI_FILE );

    CommandMap          commands;
    command::CExtract   extract;
    command::CList      list;
    commands.insert( "extract", &extract );
    commands.insert( "list", &list );

    QString command_list( QStringList( commands.keys() ).join( "|" ) );
    parser.addPositionalArgument( "command", app.translate("main", "the command to execute, use <command> --help for detailed information"), command_list );
    parser.parse( app.arguments() );
    const QStringList args( parser.positionalArguments() );
    if( args.isEmpty() )
    {
        parser.showHelp( 1 );
    }

    const QString command_name( args.at(0) );
    CommandMap::iterator it_command( commands.find( command_name ) );

    if( it_command == commands.end() )
    {
        parser.showHelp( 1 );
    }

    command::ICommand* command( it_command.value() );
    parser.clearPositionalArguments();
    command->options( parser );
    parser.process( app );

    QSettings settings( parser.value( OPTION_INI_FILE), QSettings::IniFormat );

    try
    {
        return command->execute( settings, parser );
    }
    catch ( std::exception& e )
    {
        qDebug() << "Exception: " << e.what();
    }

    return 1;
}
