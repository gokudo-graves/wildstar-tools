#include "command/c_extract.h"

#include <iostream>
#include <iomanip>

#include <QDir>

#include <QDebug>

#include "wildstar/data/c_archive.h"
#include "wildstar/data/c_archive_index.h"

using wildstar::data::CArchive;
using wildstar::data::CArchiveIndex;
using wildstar::data::CIndexDirectoryNode;
using wildstar::data::CIndexFileNode;

namespace command {

//------------------------------------------------------------------------------
const QString               CExtract::NAME( "extract" );
const QCommandLineOption    CExtract::OPTION_FULL_PATH(QStringList() << "f" << "full-path", "create the full source path at the destination");

//------------------------------------------------------------------------------
CExtract::CExtract()
{
}

//------------------------------------------------------------------------------
const QString&
CExtract::name() const
{
    return NAME;
}

//------------------------------------------------------------------------------
void
CExtract::options( QCommandLineParser& parser ) const
{
    parser.addPositionalArgument( NAME, "extract a directory or a single file", NAME );
    parser.addPositionalArgument( "archive-file", "the archive file", "*.archive" );
    parser.addPositionalArgument( "source", "the directory or file to extract", "[directory|file]" );
    parser.addPositionalArgument( "destination", "the path to extract to, defaults to the current folder", "[destination]" );

    parser.addOption( OPTION_FULL_PATH );
}

//------------------------------------------------------------------------------
void
CExtract::execute( QSettings&, QCommandLineParser& parser )
{
    const QStringList args( parser.positionalArguments() );

    if( args.size() < 3 || args.size() > 4 )
    {
        parser.showHelp( 1 );
    }
    QString archive_file_path( args.at( 1 ) )
          , destination( args.size() == 4 ? args.at( 3 ) : "" )
          , source( args.size() > 2 ? args.at( 2 ) : "" )
          ;

    archive_.read( archive_file_path );

    QFileInfo   file_info( archive_file_path );
    QString     index_file_name( file_info.completeBaseName() + ".index" );
    QString     index_file_path( file_info.dir().filePath( index_file_name ) );
    index_.read( index_file_path );

    if( parser.isSet( OPTION_FULL_PATH ) )
    {
        QFileInfo   source_info( source );
        QDir        out_path( destination );
        destination = out_path.filePath( source_info.path() );
    }

    const CIndexDirectoryNode* directory( index_.directory( source ) );
    if( directory == NULL )
    {
        extractFile( index_.file( source ), destination );
    }
    else
    {
        extractDirectory( directory, destination );
    }
    emit finished( 0 );
}

//------------------------------------------------------------------------------
void
CExtract::extractDirectory( const wildstar::data::CIndexDirectoryNode* node, QString destination )
{
    if( node == NULL )
    {
        qWarning() << "Directory not found in index.\n";
        emit finished( 1 );
        return;
    }

    QDir out_path( destination );
    destination = out_path.filePath( node->name() );

    foreach( const CIndexFileNode* const & file, node->files() )
    {
        extractFile( file, destination );
    }

    foreach( const CIndexDirectoryNode* const & directory, node->directories() )
    {
        extractDirectory( directory, destination );
    }
}

//------------------------------------------------------------------------------
void
CExtract::extractFile(const wildstar::data::CIndexFileNode* node, const QString& destination )
{
    if( node == NULL )
    {
        qWarning() << "File not found in index.\n";
        emit finished( 1 );
        return;
    }
    if( !archive_.contains( node->hash() ) )
    {
        qWarning() << qPrintable( node->hash().toHex() ) << ": File hash not found in archive.\n";
        emit finished( 1 );
        return;
    }
    QDir::current().mkpath( destination );
    QDir        out_path( destination );
    QString     out_file_path( out_path.filePath( node->name() ) );
    QFile       out( out_file_path );
    std::cout << "extracting: " << qPrintable( out_file_path ) << "\n";
    out.open( QIODevice::WriteOnly );
    archive_.extractFile( *node, out );
    out.close();
}

//------------------------------------------------------------------------------

}
