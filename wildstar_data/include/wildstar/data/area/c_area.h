#ifndef WILDSTAR_DATA_AREA_C_AREA_H
#define WILDSTAR_DATA_AREA_C_AREA_H

#include <QDataStream>

#include "../i_streamable.h"

namespace wildstar
{
    namespace data
    {
        namespace area
        {
            class WILDSTAR_DATA_SHARED CArea : public IStreamable
            {
            public:
                CArea();

                virtual void read( QDataStream& stream );
            };
        }
    }
}

#endif // WILDSTAR_DATA_AREA_C_AREA_H
