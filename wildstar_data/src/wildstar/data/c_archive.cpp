#include "wildstar/data/c_archive.h"

#include <cstring>

#include <QBuffer>
#include <QDataStream>
#include <QStringList>

#include <QDebug>

#include "wildstar/data/exception.h"

namespace wildstar
{
    namespace data
    {
        //----------------------------------------------------------------------
        CArchive::CArchive( const QString& file_name ) :
            package_( file_name )
        {
            clear();
        }

        //----------------------------------------------------------------------
        CArchive::~CArchive()
        {
        }

        //----------------------------------------------------------------------
        void
        CArchive::open( const QString& file_name )
        {
            clear();
            package_.open( file_name );

            loadHeader();
            checkHeader();

            loadFiles();
        }

        //----------------------------------------------------------------------
        void
        CArchive::writeBlock( quint32 block, QIODevice& destination )
        {
            destination.write( package_.readBlock( block ) );
        }

        //----------------------------------------------------------------------
        bool
        CArchive::contains( const CHash& hash ) const
        {
            return files_.contains( hash );
        }

        //----------------------------------------------------------------------
        const CArchive::File&
        CArchive::file( const CHash& hash ) const
        {
            return files_.value( hash );
        }

        //----------------------------------------------------------------------
        void
        CArchive::clear()
        {
            std::memset( &header_, 0, sizeof( header_ ) );
            files_.clear();
        }

        //----------------------------------------------------------------------
        void
        CArchive::loadHeader()
        {
            QDataStream stream( package_.readTypeBlock() );
            stream.setByteOrder( QDataStream::LittleEndian );
            stream >> header_;
        }

        //----------------------------------------------------------------------
        void
        CArchive::loadFiles()
        {
            QDataStream stream( package_.readBlock( header_.file_descriptions_block_index ) );
            stream.setByteOrder( QDataStream::LittleEndian );
            for( quint32 i(0); i < header_.file_count; ++i )
            {
                File    file;
                stream >> file;
                if( files_.contains( file.hash ) )
                {
                    throw EDuplicatedHash();
                }
                files_.insert( file.hash, file );
            }
        }

        //----------------------------------------------------------------------
        void
        CArchive::checkHeader() const
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
        QDataStream&
        operator>>( QDataStream& stream, CArchive::Header& header )
        {
            stream >> header.magic >> header.version
                   >> header.file_count >> header.file_descriptions_block_index
                   ;

            return stream;
        }

        //----------------------------------------------------------------------
        QDataStream&
        operator>>( QDataStream& stream, CArchive::File& file )
        {
            stream >> file.block_index >> file.hash >> file.size;

            return stream;
        }

        //----------------------------------------------------------------------
    }
}
