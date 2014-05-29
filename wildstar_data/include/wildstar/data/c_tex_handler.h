#ifndef WILDSTAR_DATA_C_TEX_HANDLER_H
#define WILDSTAR_DATA_C_TEX_HANDLER_H

#include <QImageIOHandler>

#include "global.h"

namespace wildstar
{
    namespace data
    {
        class WILDSTAR_DATA_SHARED CTexHandler : public QImageIOHandler
        {
        public:
            struct Header
            {
                quint32  magic;
                quint32  version;
            };

            enum {
                MAGIC                   = 0x5041434B // PACK
              , VERSION                 = 1
              , MINIMUM_FILE_SIZE       = 0x240
              , HEADER_SIZE             = 0x230
              , BLOCK_DESCRIPTION_SIZE  = 0x10
              , MINIMUM_BLOCK_OFFSET    = MINIMUM_FILE_SIZE
            };

            explicit CTexHandler();
            virtual ~CTexHandler() {}

        protected:

        private:
        };
    }
}
#endif // WILDSTAR_DATA_C_TEX_HANDLER_H
