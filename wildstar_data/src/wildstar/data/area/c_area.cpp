#include "wildstar/data/area/c_area.h"

#include "wildstar/data/exception.h"

namespace wildstar
{
    namespace data
    {
        namespace area
        {
            //------------------------------------------------------------------
            CArea::CArea()
            {
            }

            //------------------------------------------------------------------
            CArea::~CArea()
            {
            }

            //------------------------------------------------------------------
            void
            CArea::read( QDataStream& stream )
            {
                quint32 magic( 0 ), version( 0 );
                stream >> magic >> version;
                if( magic != MAGIC_AREA )
                {
                    throw EInvalidFileSignature();
                }

                if( version != VERSION )
                {
                    throw EInvalidFileVersion();
                }

                stream >> magic;
                if( magic == MAGIC_CHUNK )
                {
                    readChunks( stream );
                }
            }

            //------------------------------------------------------------------
            const CArea::ChunkList&
            CArea::chunks() const
            {
                return chunks_;
            }

            //------------------------------------------------------------------
            void
            CArea::readChunks( QDataStream& stream )
            {
                quint32 size( 0 );
                stream >> size;
                const QIODevice *device( stream.device() );
                qint64 end( device->pos() + size );
                while( device->pos() < end )
                {
                    CChunk chunk;
                    stream >> chunk;
                    chunks_.push_back( chunk );
                }
            }

            //------------------------------------------------------------------
        }
    }
}
