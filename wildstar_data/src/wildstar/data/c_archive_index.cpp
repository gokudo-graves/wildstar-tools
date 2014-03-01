#include "wildstar/data/c_archive_index.h"

#include <cstring>

#include <QBuffer>
#include <QDataStream>
#include <QFileInfo>
#include <QStringList>

#include <QDebug>

#include "wildstar/data/exception.h"

namespace wildstar
{
    namespace data
    {
        //----------------------------------------------------------------------
        QString CArchiveIndex::SEPERATOR("/");

        //----------------------------------------------------------------------
        CArchiveIndex::CArchiveIndex( const QString& file_name ) :
            package_( file_name )
          , root_( NULL )
        {
            clear();
        }

        //----------------------------------------------------------------------
        CArchiveIndex::~CArchiveIndex()
        {
        }

        //----------------------------------------------------------------------
        void
        CArchiveIndex::open( const QString& file_name )
        {
            clear();
            package_.open( file_name );

            loadHeader();
            checkHeader();
            root_.load( header_.root_block, package_ );
        }

        //----------------------------------------------------------------------
        void
        CArchiveIndex::clear()
        {
            std::memset( &header_, 0, sizeof( header_) );
            root_.clear();
        }

        //----------------------------------------------------------------------
        void
        CArchiveIndex::loadHeader()
        {
            QDataStream stream( package_.readTypeBlock() );
            stream.setByteOrder( QDataStream::LittleEndian );
            stream >> header_;
        }

        //----------------------------------------------------------------------
        void
        CArchiveIndex::checkHeader() const
        {
            if( header_.magic != MAGIC )
            {
                throw EInvalidFileSignature();
            }

            if( header_.version != VERSION )
            {
                throw EInvalidFileVersion();
            }
        }

        //----------------------------------------------------------------------
        const CIndexDirectoryNode&
        CArchiveIndex::root() const
        {
            return root_;
        }

        //----------------------------------------------------------------------
        const CIndexDirectoryNode*
        CArchiveIndex::directory( const QString& path ) const
        {
            const CIndexDirectoryNode* node( &root_ );
            QStringList paths( path.split( SEPERATOR, QString::SkipEmptyParts ) );
            while( !paths.isEmpty() && node != NULL )
            {
                QString name( paths.front() );
                node = node->directory( name );
                paths.pop_front();
            }

            return node;
        }

        //----------------------------------------------------------------------
        const CIndexFileNode*
        CArchiveIndex::file( const QString& path ) const
        {
            QFileInfo path_info( path );
            const CIndexDirectoryNode* directory_node( directory( path_info.path() ) );

            if( directory_node != NULL )
            {
                return directory_node->file( path_info.fileName() );
            }

            return NULL;
        }
        
        //----------------------------------------------------------------------
        QDataStream&
        operator>>( QDataStream& stream, CArchiveIndex::Header& header )
        {
            stream >> header.magic >> header.version
                   >> header.client_build >> header.root_block
                   ;

            return stream;
        }

        //----------------------------------------------------------------------
    }
}
