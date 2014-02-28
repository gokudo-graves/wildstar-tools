#include "c_list_command.h"

#include <iostream>
#include <iomanip>

#include "wildstar/data/c_archive_index.h"

using wildstar::data::CArchiveIndex;
using wildstar::data::CIndexDirectoryNode;
using wildstar::data::CIndexFileNode;

//------------------------------------------------------------------------------
const QCommandLineOption    CListCommand::OPTION_SUB_FOLDER(QStringList() << "s" << "sub-folder", "application-parameter-sub-folder", "sub-folder");
const QCommandLineOption    CListCommand::OPTION_LONG_LISTING(QStringList() << "l" << "long-listing", "application-parameter-long-listing");
const QCommandLineOption    CListCommand::OPTION_NO_DIRECTORIES(QStringList() << "d" << "no-directories", "application-parameter-no-directories");

//------------------------------------------------------------------------------
CListCommand::CListCommand() :
    long_listing_( false )
  , show_directories_( true )
{
}

//------------------------------------------------------------------------------
void
CListCommand::options( QCommandLineParser& parser ) const
{
    parser.addPositionalArgument("list", "application-parameter-command-list", "list");
    parser.addPositionalArgument("index-file", "application-parameter-index-file", "*.index");

    parser.addOption( OPTION_SUB_FOLDER );
    parser.addOption( OPTION_LONG_LISTING );
    parser.addOption( OPTION_NO_DIRECTORIES );
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
    QString path( parser.value( OPTION_SUB_FOLDER ) );
    const CIndexDirectoryNode* node( file.directory( path ) );
    if( node == NULL )
    {
        std::cout << qPrintable(path) << ": Directory not found.\n";
        return 1;
    }
    long_listing_ = parser.isSet( OPTION_LONG_LISTING );
    show_directories_ = !parser.isSet( OPTION_NO_DIRECTORIES );
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
        if( show_directories_ )
        {
            if( long_listing_  )
            {
                std::cout << std::setw(21) << " ";
            }
            std::cout << qPrintable( prefix ) << qPrintable( name ) << "\n";
        }
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
