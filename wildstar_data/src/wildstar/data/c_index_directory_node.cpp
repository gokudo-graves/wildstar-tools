#include "wildstar/data/c_index_directory_node.h"

#include <QBuffer>
#include <QDataStream>
#include <QDebug>

#include "wildstar/data/exception.h"

namespace wildstar
{
    namespace data
    {
        //----------------------------------------------------------------------
        CIndexDirectoryNode::CIndexDirectoryNode( CIndexDirectoryNode* parent ) :
            AIndexNode( parent )
        {
        }

        //----------------------------------------------------------------------
        CIndexDirectoryNode::~CIndexDirectoryNode()
        {
            clear();
        }

        //----------------------------------------------------------------------
        void
        CIndexDirectoryNode::clear()
        {
            qDeleteAll( directories_ );
            qDeleteAll( files_ );
        }

        //----------------------------------------------------------------------
        void
        CIndexDirectoryNode::load( quint32 block_index, CPackage& package )
        {
            clear();
            QByteArray block( package.readBlock( block_index ) );
            QDataStream stream( block );
            stream.setByteOrder( QDataStream::LittleEndian );

            Header header;
            stream >> header;

            QList<NameEntry>   entries;
            entries.reserve( header.directory_count + header.file_count );

            QList<Directory>    directories;
            directories.reserve( header.directory_count );
            directories_.reserve( header.directory_count );
            for( quint32 i(0); i < header.directory_count; ++i )
            {
                quint32 name_offset( 0 ), block_index( 0 );
                stream >> name_offset >> block_index;
                CIndexDirectoryNode* node( new CIndexDirectoryNode( this ) );
                directories_.push_back( node );
                directories.push_back( Directory( block_index, node ) );
                entries.push_back( NameEntry( name_offset, node ));
            }

            files_.reserve( header.file_count );
            for( quint32 i(0); i < header.file_count; ++i )
            {
                quint32 name_offset( 0 );
                CIndexFileNode* node( new CIndexFileNode( this ) );
                files_.push_back( node );
                stream >> name_offset >> node;
                entries.push_back( NameEntry( name_offset, node ) );
            }

            size_t directory_data_size( DIRECTORY_ENTRY_SIZE * header.directory_count );
            size_t file_data_size( FILE_ENTRY_SIZE * header.file_count );
            size_t data_size( HEADER_SIZE + directory_data_size + file_data_size );
            size_t string_data_size( block.size() - data_size );
            QByteArray strings( block.right( string_data_size ) );

            NameEntry entry;
            foreach( entry, entries ) {
                if( entry.first >= string_data_size )
                {
                    throw EInvalidFile();
                }
                entry.second->setName( strings.data() + entry.first );
            }

            Directory directory;
            foreach( directory, directories ) {
                if( directory.first >= package.getBlockCount() )
                {
                    throw EInvalidFile();
                }
                directory.second->load( directory.first, package );
            }
        }

        //----------------------------------------------------------------------
        const CIndexDirectoryNode*
        CIndexDirectoryNode::directory( const QString& name ) const
        {
            foreach ( const CIndexDirectoryNode* const &directory, directories_ ) {
                if( !directory->name().compare( name ) )
                {
                    return directory;
                }
            }
            return NULL;
        }

        //----------------------------------------------------------------------
        const CIndexDirectoryNode::DirectoryList&
        CIndexDirectoryNode::directories() const
        {
            return directories_;
        }

        //----------------------------------------------------------------------
        const CIndexDirectoryNode::FileList&
        CIndexDirectoryNode::files() const
        {
            return files_;
        }

        //----------------------------------------------------------------------
        QDataStream&
        operator>>( QDataStream& stream, CIndexDirectoryNode::Header& header )
        {
            stream >> header.directory_count >> header.file_count;
            return stream;
        }

        //----------------------------------------------------------------------
    }
}
