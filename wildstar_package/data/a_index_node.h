#ifndef WILDSTAR_DATA_A_INDEX_NODE_H
#define WILDSTAR_DATA_A_INDEX_NODE_H

#include <QString>

namespace wildstar
{
    namespace data
    {
        class CIndexDirectoryNode;

        class AIndexNode
        {
        public:
            explicit AIndexNode( CIndexDirectoryNode* parent );
            virtual ~AIndexNode();

            virtual void setName( const QString& name );

        private:
            QString                 name_;
            CIndexDirectoryNode*    parent_;
        };
    }
}

#endif // WILDSTAR_DATA_A_INDEX_NODE_H
