#ifndef WILDSTAR_DATA_I_STREAMABLE_H
#define WILDSTAR_DATA_I_STREAMABLE_H

#include <QDataStream>

#include "global.h"

namespace wildstar
{
    namespace data
    {
        class WILDSTAR_DATA_SHARED IStreamable
        {
        public:
            IStreamable(){}

            virtual void read( QDataStream& stream ) = 0;
        };

        WILDSTAR_DATA_SHARED QDataStream& operator>>( QDataStream& stream, IStreamable& data );
    }
}

#endif // WILDSTAR_DATA_I_STREAMABLE_H
