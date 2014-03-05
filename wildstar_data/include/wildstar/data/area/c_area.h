#ifndef WILDSTAR_DATA_AREA_C_AREA_H
#define WILDSTAR_DATA_AREA_C_AREA_H

#include <QDataStream>
#include <QList>

#include "../i_streamable.h"
#include "c_chunk.h"

namespace wildstar
{
    namespace data
    {
        namespace area
        {
            class WILDSTAR_DATA_SHARED CArea : public IStreamable
            {
            public:
                enum  {
                    MAGIC_AREA      = 0x61726561 // 'area'
                  , MAGIC_AREA_LOW  = 0x41524541 // 'AREA'
                  , MAGIC_CHUNK     = 0x43484E4B // 'CHNK'
                  , VERSION         = 0
                };

                typedef QList<CChunk>   ChunkList;

                CArea();

                virtual ~CArea();

                virtual void read( QDataStream& stream );

                virtual const ChunkList& chunks() const;

            protected:
                virtual void readChunks( QDataStream& stream );

            private:
                ChunkList   chunks_;
            };
        }
    }
}

#endif // WILDSTAR_DATA_AREA_C_AREA_H
