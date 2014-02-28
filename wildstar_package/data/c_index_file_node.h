#ifndef WILDSTAR_DATA_C_INDEX_FILE_NODE_H
#define WILDSTAR_DATA_C_INDEX_FILE_NODE_H

#include <QString>

#include "a_index_node.h"

namespace wildstar
{
    namespace data
    {
        class CIndexDirectoryNode;

        class CIndexFileNode : public AIndexNode
        {
        public:
            enum {
                HASH_LENGTH = 20
            };

            explicit CIndexFileNode( CIndexDirectoryNode* parent );
            virtual ~CIndexFileNode();

            virtual void read( QDataStream& stream );

        private:
            quint32     unknown_04_;
            quint64     file_time_;
            quint64     size_;
            quint64     compressed_size_;
            char        hash_[HASH_LENGTH]; // sha-1
            quint32     unknown_34_; // mabye padding to put sha-1 in 3 uint64
        };

        QDataStream& operator>>( QDataStream& stream, CIndexFileNode* file );

    }
}

#endif // WILDSTAR_DATA_C_INDEX_FILE_NODE_H
