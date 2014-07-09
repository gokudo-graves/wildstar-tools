#ifndef WILDSTAR_DATA_C_ARCHIVE_H
#define WILDSTAR_DATA_C_ARCHIVE_H

#include <QMap>

#include "c_archive_index.h"
#include "exception.h"

namespace wildstar
{
    namespace data
    {
        //----------------------------------------------------------------------
        class WILDSTAR_DATA_SHARED EDuplicatedHash : public EInvalidFile
        {
        public:
            EDuplicatedHash() {}
            virtual ~EDuplicatedHash() throw() {}

            virtual const char* what() const throw() {
                return "Invalid file. Duplicate HashEntry";
            }
        };

        //----------------------------------------------------------------------
        class WILDSTAR_DATA_SHARED CArchive
        {
        public:
            struct Header
            {
                quint32     magic;
                quint32     version;
                quint32     file_count;
                quint32     file_descriptions_block_index;
            };

            struct File
            {
                quint32     block_index;
                CHash       hash;
                quint64     size;
            };

            enum {
                MAGIC       = 0x41415243 // AARC
              , VERSION     = 2
            };

            typedef QMap<CHash, File>     FileMap;

            explicit CArchive();
            virtual ~CArchive();

            virtual void read( const QString& file_name = QString() );
            virtual void writeBlock( quint32 block, QIODevice& destination );
            virtual void extractFile( const CIndexFileNode& node, QIODevice& destination );

            virtual bool contains( const CHash& hash ) const;

        protected:
            virtual void clear();

            virtual void loadHeader();
            virtual void loadFiles();

            virtual void checkHeader() const;

        private:
            CPackage    package_;
            Header      header_;
            FileMap     files_;
        };

        WILDSTAR_DATA_SHARED QDataStream& operator>>( QDataStream& stream, CArchive::Header& header );
        WILDSTAR_DATA_SHARED QDataStream& operator>>( QDataStream& stream, CArchive::File& file );
    }
}

#endif // WILDSTAR_DATA_C_ARCHIVE_H
