/*
-----------------------------------------------------------------------------
Copyright (c) 26.02.2014 Tobias Peters <tobias.peters@kreativeffekt.at>

This file is part of Q-Gears

Q-Gears is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 2.0 (GPLv2) of the License.

Q-Gears is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
-----------------------------------------------------------------------------
*/

#include <QDebug>

#include <QCommandLineOption>
#include <QCoreApplication>

#include "c_list_command.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationVersion( "0.0.1" );

    QCommandLineParser parser;
    parser.setApplicationDescription( app.translate("main", "application-description") );
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("command", app.translate("main", "application-parameter-command"), "list|build-version");
    parser.parse( app.arguments() );
    const QStringList args( parser.positionalArguments() );
    parser.clearPositionalArguments();

    if( args.isEmpty() )
    {
        parser.showHelp( 1 );
    }

    ICommand* command( NULL );
    CListCommand list;
    const QString command_name( args.at(0) );
    if (command_name == "list") {
        command = &list;
    }
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
