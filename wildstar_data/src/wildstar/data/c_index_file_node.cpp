#include "wildstar/data/c_index_file_node.h"

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
        void
        CIndexFileNode::read( QDataStream& stream )
        {
            stream >> unknown_04_
                   >> file_time_ >> size_ >> compressed_size_ >> hash_
                   >> unknown_34_;
        }

        //----------------------------------------------------------------------
        quint64
        CIndexFileNode::size() const
        {
            return size_;
        }

        //----------------------------------------------------------------------
        quint64
        CIndexFileNode::compressedSize() const
        {
            return compressed_size_;
        }

        //----------------------------------------------------------------------
        const CHash&
        CIndexFileNode::hash() const
        {
            return hash_;
        }

        //----------------------------------------------------------------------
        QDataStream&
        operator>>( QDataStream& stream, CIndexFileNode* file )
        {
            file->read( stream );
            return stream;
        }

        //----------------------------------------------------------------------
    }
}
