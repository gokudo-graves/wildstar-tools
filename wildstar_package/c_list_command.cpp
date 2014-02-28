#include "c_list_command.h"

#include <iostream>

#include "wildstar/data/c_archive_index.h"

using wildstar::data::CArchiveIndex;
using wildstar::data::CIndexDirectoryNode;
using wildstar::data::CIndexFileNode;

//------------------------------------------------------------------------------
const QCommandLineOption    CListCommand::SUB_FOLDER_OPTION(QStringList() << "s" << "sub-folder", "application-parameter-sub-folder", "sub-folder");

//------------------------------------------------------------------------------
CListCommand::CListCommand()
{
}

//------------------------------------------------------------------------------
void
CListCommand::options( QCommandLineParser& parser ) const
{
    parser.addPositionalArgument("list", "application-parameter-command-list", "list <options>");
    parser.addPositionalArgument("filename", "application-parameter-filename", "*.index");

    parser.addOption( SUB_FOLDER_OPTION );
}

//------------------------------------------------------------------------------
int
CListCommand::execute( QCommandLineParser& parser ) const
{
    const QStringList args( parser.positionalArguments() );

    if( args.size() != 2 )
    {
        parser.showHelp( 1 );
    }
    QString filename( args.at( 1 ) );
    CArchiveIndex file( filename );

    file.open();
    QString path( parser.value( SUB_FOLDER_OPTION ) );
    const CIndexDirectoryNode* node( file.directory( path ) );
    if( node == NULL )
    {
        std::cout << qPrintable(path) << ": Directory not found.\n";
        return 1;
    }
    print( node );
    return 0;
}

//------------------------------------------------------------------------------
void
CListCommand::print( const CIndexDirectoryNode* node, const QString& path ) const
{
    QString prefix( path );
    if( !prefix.isEmpty() )
    {
        prefix += "/";
    }

    foreach( const CIndexDirectoryNode* const & directory, node->directories() )
    {
        const QString& name( directory->name() );
        std::cout << qPrintable( prefix ) << qPrintable( name ) << "\n";
        print( directory, prefix + name );
    }

    foreach( const CIndexFileNode* const & file, node->files() )
    {
        const QString& name( file->name() );
        std::cout << qPrintable( prefix ) << qPrintable( name )
                  << "\n";
    }
}

//------------------------------------------------------------------------------
