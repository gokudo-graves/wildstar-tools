#ifndef WILDSTAR_DATA_C_ARCHIVE_INDEX_H
#define WILDSTAR_DATA_C_ARCHIVE_INDEX_H

#include "c_index_directory_node.h"
#include "c_package.h"

namespace wildstar
{
    namespace data
    {
        class CArchiveIndex
        {
        public:
            struct Header
            {
                quint32  magic;
                quint32  version;
                quint32  client_build;
                quint32  root_block;
            };

            enum {
                MAGIC        = 0x41494458 // AIDX
              , VERSION     = 1
            };

            explicit CArchiveIndex( const QString& file_name );
            virtual ~CArchiveIndex();

            virtual void open();

            const CIndexDirectoryNode& root() const;

        protected:
            virtual void clear();

            virtual void loadHeader();

            virtual void checkHeader() const;

        private:
            CPackage                package_;
            Header                  header_;
            CIndexDirectoryNode     root_;
        };

        QDataStream& operator>>( QDataStream& stream, CArchiveIndex::Header& header );
    }
}

#endif // WILDSTAR_DATA_C_ARCHIVE_INDEX_H
