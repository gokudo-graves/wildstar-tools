#ifndef WILDSTAR_DATA_C_PACKAGE_H
#define WILDSTAR_DATA_C_PACKAGE_H

#include <QFile>

#include "s_package_header.h"

namespace wildstar
{
    namespace data
    {
        class CPackage
        {
        public:

            enum {
                MAGIC               = 0x5041434B // PACK
              , MINIMUM_FILE_SIZE   = 0x240
              , VERSION             = 1
            };

            explicit CPackage( const QString & file_name );

            virtual void load();

        protected:
            virtual bool isFileValid();
            virtual bool isHeaderValid();

        private:
            QFile           file_;
            SPackageHeader  header_;
        };
    }
}
#endif // WILDSTAR_DATA_C_PACKAGE_H
