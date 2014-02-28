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
        CArchive::open()
        {
            clear();
            package_.open();

            loadHeader();
            checkHeader();
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
                   >> header.unkown_8 >> header.unkown_a
                   ;

            return stream;
        }

        //----------------------------------------------------------------------
    }
}
