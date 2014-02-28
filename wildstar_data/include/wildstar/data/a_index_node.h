#ifndef WILDSTAR_DATA_A_INDEX_NODE_H
#define WILDSTAR_DATA_A_INDEX_NODE_H

#include <QString>

#include "global.h"

namespace wildstar
{
    namespace data
    {
        class CIndexDirectoryNode;

        class WILDSTAR_DATA_SHARED AIndexNode
        {
        public:
            explicit AIndexNode( CIndexDirectoryNode* parent );
            virtual ~AIndexNode();

            virtual const QString& name() const;
            virtual void setName( const char* name );

        protected:

        private:
            QString                 name_;
            CIndexDirectoryNode*    parent_;
        };
    }
}

#endif // WILDSTAR_DATA_A_INDEX_NODE_H
