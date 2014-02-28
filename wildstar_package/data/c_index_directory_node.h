#ifndef WILDSTAR_DATA_C_INDEX_DIRECTORY_NODE_H
#define WILDSTAR_DATA_C_INDEX_DIRECTORY_NODE_H

#include <QString>

#include "a_index_node.h"
#include "c_index_file_node.h"
#include "c_package.h"

namespace wildstar
{
    namespace data
    {
        class CIndexFileNode;

        class CIndexDirectoryNode : public AIndexNode
        {
        public:
            struct Header
            {
                quint32  directory_count;
                quint32  file_count;
            };

            struct Data
            {
                quint32  name_offset;
                quint32  block_index;
            };

            enum {
                HEADER_SIZE             = 0x8
              , DIRECTORY_ENTRY_SIZE    = 0x8
              , FILE_ENTRY_SIZE         = 0x38
            };

            explicit CIndexDirectoryNode( CIndexDirectoryNode* parent = NULL );
            virtual ~CIndexDirectoryNode();

            virtual void clear();
            virtual void load( quint32 block_index, CPackage& package );

        protected:

        private:
            QList<CIndexDirectoryNode*>     directories_;
            QList<CIndexFileNode*>          files_;
        };

        QDataStream& operator>>( QDataStream& stream, CIndexDirectoryNode::Header& header );
        QDataStream& operator>>( QDataStream& stream, CIndexDirectoryNode::Data& data );
    }
}

#endif // WILDSTAR_DATA_C_INDEX_DIRECTORY_NODE_H
