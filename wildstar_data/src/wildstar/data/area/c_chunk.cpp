#include "wildstar/data/area/c_chunk.h"

#include <QDebug>

#include <QByteArray>

namespace wildstar
{
    namespace data
    {
        namespace area
        {
            //------------------------------------------------------------------
            CChunk::CChunk()
            {
            }

            //------------------------------------------------------------------
            CChunk::~CChunk()
            {

            }

            //------------------------------------------------------------------
            void
            CChunk::read( QDataStream& chunk_stream )
            {
                quint32 size;
                chunk_stream >> size;
                size &= 0xffffff;
                QByteArray data( size, 0 );
                chunk_stream.readRawData( data.data(), size );
                QDataStream stream( data );
                stream.setByteOrder( QDataStream::LittleEndian );

                stream >> flags_;

                if( flags_ & LAYER_0x00000001 )
                {
                    stream >> height_map;
                }

                if( flags_ & PROPERTY_0x00000002 )
                {
                    stream >> texture_ids;
                }

                if( flags_ & LAYER_0x00000004 )
                {
                    stream >> texture_blend;
                }

                if( flags_ & HEIGHT_MAP )
                {
                    stream >> color_map;
                }

                if(    flags_ & UNKNOWN_0x00000040
                    || flags_ & UNKNOWN_0x00000080
                  )
                {
                    stream >> unknown_44EE;
                }

                if( flags_ & SHADOW_MAP )
                {
                    stream >> shadow_map;
                }

                if( flags_ & LAYER_0x00010000 )
                {
                    stream >> unknown_55BF;
                }

                if( flags_ & PROPERTY_0x00200000 )
                {
                    stream >> unknown_65BE;
                }

                if( flags_ & PROPERTY_0x00400000 )
                {
                    stream >> unknown_65BF;
                }

                if( flags_ & LAYER_0x04000000 )
                {
                    stream >> unknown_0x04000000;
                }

                if( flags_ & LAYER_0x08000000 )
                {
                    stream >> unknown_65CF;
                }

                if( flags_ & PROPERTY_0x10000000 )
                {
                    stream >> unknown_75CF;
                }

                if( flags_ & LAYER_0x20000000 )
                {
                    stream >> unknown_75DF;
                }
            }

            //------------------------------------------------------------------
        }
    }
}
