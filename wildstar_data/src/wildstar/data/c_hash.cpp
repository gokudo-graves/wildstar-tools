#include "wildstar/data/c_hash.h"

#include <QDebug>

namespace wildstar
{
    namespace data
    {
        //----------------------------------------------------------------------
        CHash::CHash() :
            data_( LENGTH, 0 )
        {
        }

        //----------------------------------------------------------------------
        CHash::~CHash()
        {
        }

        //----------------------------------------------------------------------
        void
        CHash::clear()
        {
            data_.fill( 0, LENGTH );
        }

        //----------------------------------------------------------------------
        char*
        CHash::data()
        {
            return data_.data();
        }

        //----------------------------------------------------------------------
        QByteArray
        CHash::toHex() const
        {
            return data_.toHex();
        }

        //----------------------------------------------------------------------
        QDataStream&
        operator>>( QDataStream& stream, CHash& hash )
        {
            hash.clear();
            stream.readRawData( hash.data(), CHash::LENGTH );
            return stream;
        }

        //----------------------------------------------------------------------
    }
}
