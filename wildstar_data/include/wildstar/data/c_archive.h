#ifndef WILDSTAR_DATA_C_ARCHIVE_H
#define WILDSTAR_DATA_C_ARCHIVE_H

#include "c_archive_index.h"

namespace wildstar
{
    namespace data
    {
        class WILDSTAR_DATA_SHARED CArchive
        {
        public:
            struct Header
            {
                quint32  magic;
                quint32  version;
                quint32  unkown_8;
                quint32  unkown_a;
            };

            enum {
                MAGIC       = 0x41415243 // AARC
              , VERSION     = 2
            };

            explicit CArchive( const QString& file_name );
            virtual ~CArchive();

            virtual void open();
            virtual void extractBlock( quint32 block, QIODevice& destination );

        protected:
            virtual void clear();

            virtual void loadHeader();

            virtual void checkHeader() const;

        private:
            CPackage    package_;
            Header      header_;

        };

        WILDSTAR_DATA_SHARED QDataStream& operator>>( QDataStream& stream, CArchive::Header& header );
    }
}

#endif // WILDSTAR_DATA_C_ARCHIVE_H
