#include "data/c_index_directory_node.h"

#include <QBuffer>
#include <QDataStream>

namespace wildstar
{
    namespace data
    {
        //----------------------------------------------------------------------
        CIndexDirectoryNode::CIndexDirectoryNode( CIndexDirectoryNode* parent ) :
            AIndexNode( parent )
        {
        }

        //----------------------------------------------------------------------
        CIndexDirectoryNode::~CIndexDirectoryNode()
        {
            clear();
        }

        //----------------------------------------------------------------------
        void
        CIndexDirectoryNode::clear()
        {
            qDeleteAll( directories_ );
            qDeleteAll( files_ );
        }

        //----------------------------------------------------------------------
        void
        CIndexDirectoryNode::load( quint32 block_index, CPackage& package )
        {
            clear();
            QByteArray block( package.readBlock( block_index ) );
            QDataStream stream( block );
            stream.setByteOrder( QDataStream::LittleEndian );

            Header header;
            stream >> header;

            //stream.setByteOrder( QDataStream::LittleEndian );
            //buffer.size();
        }

        //----------------------------------------------------------------------
        QDataStream&
        operator>>( QDataStream& stream, CIndexDirectoryNode::Header& header )
        {
            stream >> header.directory_count >> header.file_count;
            return stream;
        }

        //----------------------------------------------------------------------
        QDataStream&
        operator>>( QDataStream& stream, CIndexDirectoryNode::Data& data )
        {
            stream >> data.name_offset >> data.block_index;
            return stream;
        }

        //----------------------------------------------------------------------
    }
}
