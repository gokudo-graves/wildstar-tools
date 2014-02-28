#include "wildstar/data/a_index_node.h"

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
        const QString&
        AIndexNode::name()
        {
            return name_;
        }

        //----------------------------------------------------------------------
        void
        AIndexNode::setName( const char* name )
        {
            name_ = name;
        }

        //----------------------------------------------------------------------
    }
}
