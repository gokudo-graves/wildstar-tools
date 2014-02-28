#include "data/a_index_node.h"

#include <QBuffer>
#include <QDataStream>

namespace wildstar
{
    namespace data
    {
        //----------------------------------------------------------------------
        AIndexNode::AIndexNode( CIndexDirectoryNode* parent ) :
            parent_( parent )
        {
        }

        //----------------------------------------------------------------------
        AIndexNode::~AIndexNode()
        {
        }

        //----------------------------------------------------------------------
        void
        AIndexNode::setName( const QString& name )
        {
            name_ = name;
        }

        //----------------------------------------------------------------------
    }
}
