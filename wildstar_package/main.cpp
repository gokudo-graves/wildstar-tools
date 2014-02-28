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

#include <iostream>

#include <QDebug>

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>

#include "wildstar/data/c_archive_index.h"
#include "wildstar/data/c_package.h"

using namespace wildstar;
using namespace wildstar::data;

void print( const CIndexDirectoryNode& node, const QString& path = "" )
{
    QString prefix( path + "/" );
    foreach( const CIndexDirectoryNode* const & directory, node.directories() ) {
        const QString& name( directory->name() );
        std::cout << qPrintable( prefix ) << qPrintable( name ) << "\n";
        print( *directory, prefix + name );
    }

    foreach( const CIndexFileNode* const & file, node.files() ) {
        const QString& name( file->name() );
        std::cout << qPrintable( prefix ) << qPrintable( name )
                  << "\n";
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationVersion( "0.0.1" );

    QCommandLineParser parser;
    parser.setApplicationDescription( app.translate("main", "application-description") );
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("filename", app.translate("main", "application-parameter-filename"), "*.index");

    QCommandLineOption sub_folder(QStringList() << "s" << "sub-folder", app.translate("main", "application-parameter-sub-folder"), "sub-folder");
    parser.addOption(sub_folder);

    parser.process( app );
    const QStringList args( parser.positionalArguments() );

    if( args.size() != 1 )
    {
        parser.showHelp( 1 );
    }
    QString filename( args.at( 0 ) );
    CArchiveIndex file( filename );

    try
    {
        file.open();
        QString path( parser.value( sub_folder ) );
        const CIndexDirectoryNode* node( file.directory( path ) );
        if( node == NULL )
        {
            std::cout << qPrintable(path) << ": Directory not found.\n";
            return 1;
        }
        print( *node );
    }
    catch ( std::exception& e )
    {
        qDebug() << "Exception: " << e.what();
        return 1;
    }

    return 0;
}
