#ifndef WILDSTAR_DATA_AREA_C_CHUNK_H
#define WILDSTAR_DATA_AREA_C_CHUNK_H

#include <QDataStream>

#include "../i_streamable.h"

namespace wildstar
{
    namespace data
    {
        namespace area
        {
            class WILDSTAR_DATA_SHARED CChunk : public IStreamable
            {
            public:
                CChunk();

                virtual void read( QDataStream& stream );
            };
        }
    }
}

#endif // WILDSTAR_DATA_AREA_C_CHUNK_H
