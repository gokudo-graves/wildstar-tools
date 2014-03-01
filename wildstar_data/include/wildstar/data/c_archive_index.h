#ifndef WILDSTAR_DATA_C_ARCHIVE_INDEX_H
#define WILDSTAR_DATA_C_ARCHIVE_INDEX_H

#include "c_index_directory_node.h"
#include "c_package.h"

namespace wildstar
{
    namespace data
    {
        class WILDSTAR_DATA_SHARED CArchiveIndex
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
                MAGIC       = 0x41494458 // AIDX
              , VERSION     = 1
            };

            typedef QList<const CIndexFileNode*>    ConstFileList;

            explicit CArchiveIndex( const QString& file_name = QString() );
            virtual ~CArchiveIndex();

            virtual void open( const QString& file_name = QString() );

            const CIndexDirectoryNode& root() const;
            const CIndexDirectoryNode* directory( const QString& path ) const;
            const CIndexFileNode* file( const QString& path ) const;

        protected:
            virtual void clear();

            virtual void loadHeader();

            virtual void checkHeader() const;

        private:
            CPackage                package_;
            Header                  header_;
            CIndexDirectoryNode     root_;

            static QString          SEPERATOR;
        };

        WILDSTAR_DATA_SHARED QDataStream& operator>>( QDataStream& stream, CArchiveIndex::Header& header );
    }
}

#endif // WILDSTAR_DATA_C_ARCHIVE_INDEX_H
