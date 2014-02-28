#ifndef WILDSTAR_DATA_C_INDEX_FILE_NODE_H
#define WILDSTAR_DATA_C_INDEX_FILE_NODE_H

#include <QString>

#include "c_index_directory_node.h"

namespace wildstar
{
    namespace data
    {
        class CIndexFileNode : public AIndexNode
        {
        public:
            struct Data
            {
                quint32     name_offset;
                quint32     unknown_00;
                quint64     file_time;
                quint64     file_size[2];
                char        hash[20]; // sha-1
                quint32     unknown_02; // mabye padding to put sha-1 in 3 uint64
            };

            explicit CIndexFileNode( CIndexDirectoryNode* parent );
            virtual ~CIndexFileNode();

        private:
        };

        QDataStream& operator>>( QDataStream& stream, CIndexFileNode::Data& data );
    }
}

#endif // WILDSTAR_DATA_C_INDEX_FILE_NODE_H
