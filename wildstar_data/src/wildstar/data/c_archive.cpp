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
        }

        //----------------------------------------------------------------------
        void
        CArchive::extractBlock( quint32 block, QIODevice& destination )
        {
            destination.write( package_.readBlock( block ) );
        }

        //----------------------------------------------------------------------
        void
        CArchive::clear()
        {
            std::memset( &header_, 0, sizeof( header_ ) );
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
    }
}
