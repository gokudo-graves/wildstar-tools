#include "command/c_list.h"

#include <iostream>
#include <iomanip>

#include "wildstar/data/c_archive_index.h"

using wildstar::data::CArchiveIndex;
using wildstar::data::CIndexDirectoryNode;
using wildstar::data::CIndexFileNode;

namespace command {

//------------------------------------------------------------------------------
const QString               CList::NAME( "list" );
const QCommandLineOption    CList::OPTION_LONG_LISTING(QStringList() << "l" << "long-listing", "show a more detailed listing");
const QCommandLineOption    CList::OPTION_NO_DIRECTORIES(QStringList() << "d" << "no-directories", "don't include directories in output");

//------------------------------------------------------------------------------
CList::CList() :
    long_listing_( false )
  , show_directories_( true )
{
}

//------------------------------------------------------------------------------
const QString&
CList::name() const
{
    return NAME;
}

//------------------------------------------------------------------------------
void
CList::options( QCommandLineParser& parser ) const
{
    parser.addPositionalArgument( NAME, "list files and directories in an index file", NAME );
    parser.addPositionalArgument( "index-file", "the archive index file", "*.index" );
    parser.addPositionalArgument( "source", "optional path to a directory or file to list", "[directory|file]" );

    parser.addOption( OPTION_LONG_LISTING );
    parser.addOption( OPTION_NO_DIRECTORIES );
}

//------------------------------------------------------------------------------
void CList::execute( QSettings&, QCommandLineParser& parser )
{
    const QStringList args( parser.positionalArguments() );

    if( args.size() < 2 || args.size() > 3 )
    {
        parser.showHelp( 1 );
    }
    QString filename( args.at( 1 ) );
    long_listing_ = parser.isSet( OPTION_LONG_LISTING );
    show_directories_ = !parser.isSet( OPTION_NO_DIRECTORIES );

    CArchiveIndex index;
    index.read( filename );
    QString path( args.size() == 3 ? args.at( 2) : "" );

    QString prefix( path );
    if( !prefix.isEmpty() )
    {
        prefix += "/";
    }

    const CIndexFileNode* file( index.file( path ) );
    const CIndexDirectoryNode* dir( index.directory( path ) );
    if( file == NULL && dir == NULL )
    {
        // TODO: maybe use qWarning or qFaltal?? or std:cerr?
        std::cout << qPrintable(path) << ": Directory not found.\n";
        emit finished( 1 );
        return;
    }
    print( file, prefix );
    print( dir, prefix );

    emit finished( 0 );
}

//------------------------------------------------------------------------------
void
CList::print( const CIndexDirectoryNode* node, const QString& prefix ) const
{
    if( node == NULL )
    {
        return;
    }

    foreach( const CIndexDirectoryNode* const & directory, node->directories() )
    {
        const QString& name( directory->name() );
        if( show_directories_ )
        {
            if( long_listing_  )
            {
                std::cout << std::setw(62) << " " ;
            }
            std::cout << qPrintable( prefix ) << qPrintable( name ) << "\n";
        }
        print( directory, prefix + name + "/" );
    }

    foreach( const CIndexFileNode* const & file, node->files() )
    {
        print( file, prefix );
    }
}

//------------------------------------------------------------------------------
void
CList::print( const CIndexFileNode* node, const QString& prefix ) const
{
    if( node == NULL )
    {
        return;
    }

    const QString& name( node->name() );
    if( long_listing_  )
    {
        std::cout << std::setw(10) << node->size()
                  << std::setw(10) << node->compressedSize()
                  << " " << qPrintable( node->hash().toHex() )
                  << " "
                  ;
    }
    std::cout << qPrintable( prefix ) << qPrintable( name )
              << "\n";
}

//------------------------------------------------------------------------------

}
