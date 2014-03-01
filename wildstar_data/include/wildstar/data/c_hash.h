#ifndef WILDSTAR_DATA_C_HASH_H
#define WILDSTAR_DATA_C_HASH_H

#include <QByteArray>

#include "global.h"

namespace wildstar
{
    namespace data
    {
        // SHA-1
        class WILDSTAR_DATA_SHARED CHash
        {
        public:
            enum {
                LENGTH      = 20
            };

            CHash();
            virtual ~CHash();

            virtual void clear();
            virtual char* data();
            virtual QByteArray toHex() const;

        protected:

        private:
            QByteArray      data_;
        };

        WILDSTAR_DATA_SHARED QDataStream& operator>>( QDataStream& stream, CHash& hash );
    }
}

#endif // WILDSTAR_DATA_C_HASH_H
