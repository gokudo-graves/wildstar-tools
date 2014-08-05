#include <QDebug>

#include <QCommandLineOption>

#include "c_application.h"
#include "command/c_command_map.h"
#include "command/c_extract.h"
#include "command/c_list.h"
#include "command/c_patch.h"

using command::CCommandMap;
using command::ICommand;

int main(int argc, char *argv[])
{
    CApplication app(argc, argv);
    app.setApplicationVersion( "0.0.1" );

    QCommandLineParser parser;
    parser.setApplicationDescription( app.translate("main", "tool to do some basic actions on wildstar data files") );
    parser.addHelpOption();
    parser.addVersionOption();

    const QCommandLineOption    OPTION_INI_FILE(QStringList() << "i" << "ini-file", "ini file with settings to use", "[*.ini]", "wildstar.ini");
    parser.addOption( OPTION_INI_FILE );

    CCommandMap     commands;
    commands.insert( "extract", new command::CExtract() );
    commands.insert( "list"   , new command::CList()    );
    commands.insert( "patch"  , new command::CPatch()   );

    commands.options( parser );
    parser.parse( app.arguments() );
    ICommand* command( commands.get( parser ) );
    command->options( parser );
    parser.process( app );

    QSettings settings( parser.value( OPTION_INI_FILE ), QSettings::IniFormat );
    QObject::connect(
          command, &ICommand::finished
        , &app, &QCoreApplication::exit
        , Qt::QueuedConnection
    );

    QObject::connect(
          &app, &CApplication::started
        , command, &ICommand::execute
    );

    emit app.started( settings, parser );

    return app.exec();
}
