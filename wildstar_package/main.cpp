#include <QDebug>

#include <QCommandLineOption>
#include <QCoreApplication>

#include "c_extract_command.h"
#include "c_list_command.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationVersion( "0.0.1" );

    QCommandLineParser parser;
    parser.setApplicationDescription( app.translate("main", "tool to do some basic actions on wildstar data files") );
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("command", app.translate("main", "the command to execute, use <command> --help for detailed information"), "list|extract");
    parser.parse( app.arguments() );
    const QStringList args( parser.positionalArguments() );
    if( args.isEmpty() )
    {
        parser.showHelp( 1 );
    }

    QMap<QString, ICommand*>    commands;
    CExtractCommand     extract;
    CListCommand        list;
    commands.insert( "extract", &extract );
    commands.insert( "list", &list );

    ICommand* command( NULL );
    const QString command_name( args.at(0) );
    command = commands[ command_name ];

    if( command == NULL )
    {
        parser.showHelp( 1 );
    }
    parser.clearPositionalArguments();
    command->options( parser );
    parser.process( app );

    try
    {
        return command->execute( parser );
    }
    catch ( std::exception& e )
    {
        qDebug() << "Exception: " << e.what();
    }

    return 1;
}
