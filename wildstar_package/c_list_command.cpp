#include "c_list_command.h"

#include <iostream>
#include <iomanip>

#include "wildstar/data/c_archive_index.h"

using wildstar::data::CArchiveIndex;
using wildstar::data::CIndexDirectoryNode;
using wildstar::data::CIndexFileNode;

//------------------------------------------------------------------------------
const QCommandLineOption    CListCommand::SUB_FOLDER_OPTION(QStringList() << "s" << "sub-folder", "application-parameter-sub-folder", "sub-folder");
const QCommandLineOption    CListCommand::LONG_LISTING_OPTION(QStringList() << "l" << "long-listing", "application-parameter-long-listing");

//------------------------------------------------------------------------------
CListCommand::CListCommand() :
    long_listing_( false )
{
}

//------------------------------------------------------------------------------
void
CListCommand::options( QCommandLineParser& parser ) const
{
    parser.addPositionalArgument("list", "application-parameter-command-list", "list");
    parser.addPositionalArgument("index-file", "application-parameter-index-file", "*.index");

    parser.addOption( SUB_FOLDER_OPTION );
    parser.addOption( LONG_LISTING_OPTION );
}

//------------------------------------------------------------------------------
int
CListCommand::execute( QCommandLineParser& parser )
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
    long_listing_ = parser.isSet( LONG_LISTING_OPTION );
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
        if( long_listing_  )
        {
            std::cout << std::setw(21) << " ";
        }
        std::cout << qPrintable( prefix ) << qPrintable( name ) << "\n";
        print( directory, prefix + name );
    }

    foreach( const CIndexFileNode* const & file, node->files() )
    {
        const QString& name( file->name() );
        if( long_listing_  )
        {
            std::cout << std::setw(10) << file->size()
                      << std::setw(10) << file->compressed_size()
                      << " "
                      ;
        }
        std::cout << qPrintable( prefix ) << qPrintable( name )
                  << "\n";
    }
}

//------------------------------------------------------------------------------
