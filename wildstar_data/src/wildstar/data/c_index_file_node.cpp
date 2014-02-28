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
                   >> file_time_ >> size_ >> compressed_size_;
            stream.readRawData( hash_, HASH_LENGTH );
            stream >> unknown_34_;
        }

        //----------------------------------------------------------------------
        quint64
        CIndexFileNode::size() const
        {
            return size_;
        }

        //----------------------------------------------------------------------
        quint64
        CIndexFileNode::compressed_size() const
        {
            return compressed_size_;
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
