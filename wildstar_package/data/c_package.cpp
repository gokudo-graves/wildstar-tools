#include "data/c_package.h"

#include <cstring>
#include <QDataStream>

#include "data/exception.h"

namespace wildstar
{
    namespace data
    {
        //----------------------------------------------------------------------
        CPackage::CPackage( const QString & file_name ) :
            file_( file_name )
        {
            std::memset( &header_, 0, sizeof( header_) );
        }

        //----------------------------------------------------------------------
        void CPackage::load()
        {
            if( !file_.exists() )
            {
                throw EInvalidFileNotExist();
            }

            SPackageHeader header;
            if( file_.size() < sizeof(header) )
            {
                throw EInvalidFileSize();
            }

            if( !file_.open( QIODevice::ReadOnly ) )
            {
                throw EInvalidFileNotReadable();
            }

            QDataStream stream( &file_ );
            stream.setByteOrder( QDataStream::LittleEndian );
            stream >> header;

            if( header.magic != MAGIC )
            {
                throw EInvalidFileSignature();
            }

            if( header.version != VERSION )
            {
                throw EInvalidFileVersion();
            }
        }

        //----------------------------------------------------------------------
        bool CPackage::isFileValid()
        {
            return false;
        }

        //----------------------------------------------------------------------
        bool CPackage::isHeaderValid()
        {
            return false;
        }

        //----------------------------------------------------------------------
    }
}
