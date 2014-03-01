#ifndef WILDSTAR_DATA_C_INDEX_DIRECTORY_NODE_H
#define WILDSTAR_DATA_C_INDEX_DIRECTORY_NODE_H

#include <QList>
#include <QPair>
#include <QString>

#include "a_index_node.h"
#include "c_index_file_node.h"
#include "c_package.h"

namespace wildstar
{
    namespace data
    {
        class WILDSTAR_DATA_SHARED CIndexDirectoryNode : public AIndexNode
        {
        public:
            struct Header
            {
                quint32  directory_count;
                quint32  file_count;
            };

            enum {
                HEADER_SIZE             = 0x8
              , DIRECTORY_ENTRY_SIZE    = 0x8
              , FILE_ENTRY_SIZE         = 0x38
            };

            typedef QList<CIndexDirectoryNode*>     DirectoryList;
            typedef QList<CIndexFileNode*>          FileList;

            explicit CIndexDirectoryNode( CIndexDirectoryNode* parent = NULL );
            virtual ~CIndexDirectoryNode();

            virtual void clear();

            virtual void load( quint32 block_index, CPackage& package );

            virtual const CIndexDirectoryNode* directory(
                const QString& name
              , const Qt::CaseSensitivity case_sensitivity = Qt::CaseInsensitive
            ) const;

            virtual const CIndexFileNode* file(
                const QString& name
              , const Qt::CaseSensitivity case_sensitivity = Qt::CaseInsensitive
            ) const;

            virtual const DirectoryList& directories() const;

            virtual const FileList& files() const;

        protected:

        private:
            typedef QPair<quint32,AIndexNode*>              NameEntry;
            typedef QPair<quint32,CIndexDirectoryNode*>     Directory;

            DirectoryList   directories_;
            FileList        files_;
        };

        WILDSTAR_DATA_SHARED QDataStream& operator>>( QDataStream& stream, CIndexDirectoryNode::Header& header );
    }
}

#endif // WILDSTAR_DATA_C_INDEX_DIRECTORY_NODE_H
