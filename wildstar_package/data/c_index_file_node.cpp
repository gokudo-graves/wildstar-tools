#include "data/c_index_file_node.h"

#include <QBuffer>
#include <QDataStream>

namespace wildstar
{
    namespace data
    {
        //----------------------------------------------------------------------
        CIndexFileNode::CIndexFileNode( CIndexDirectoryNode* parent ) :
            AIndexNode( parent )
        {

        }

        //----------------------------------------------------------------------
        CIndexFileNode::~CIndexFileNode()
        {
        }

        //----------------------------------------------------------------------
        QDataStream&
        operator>>( QDataStream& stream, CIndexFileNode::Data& data )
        {
            return stream;
        }

        //----------------------------------------------------------------------
    }
}
