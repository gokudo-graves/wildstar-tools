#ifndef WILDSTAR_DATA_AREA_C_CHUNK_H
#define WILDSTAR_DATA_AREA_C_CHUNK_H

#include <QDataStream>

#include "../c_array.h"

namespace wildstar
{
    namespace data
    {
        namespace area
        {
            class WILDSTAR_DATA_SHARED CChunk : public IStreamable
            {
            public:
                enum Flags
                {
                    SIZE_MASK           = 0x00ffffff
                  , LAYER_0x00000001    = 0x00000001
                  , PROPERTY_0x00000002 = 0x00000002
                  , LAYER_0x00000004    = 0x00000004
                  , HEIGHT_MAP          = 0x00000008
                  , UNKNOWN_0x00000040  = 0x00000040
                  , UNKNOWN_0x00000080  = 0x00000080
                  , SHADOW_MAP          = 0x00000100
                  , LAYER_0x00010000    = 0x00010000
                  , PROPERTY_0x00200000 = 0x00200000
                  , PROPERTY_0x00400000 = 0x00400000
                  , LAYER_0x04000000    = 0x04000000
                  , LAYER_0x08000000    = 0x08000000
                  , PROPERTY_0x10000000 = 0x10000000
                  , LAYER_0x20000000    = 0x20000000
                  , UNKNOWN_FLAGS       = 0xC39EFE00
                };

                CChunk();
                virtual ~CChunk();

                virtual void read( QDataStream& stream );

            //private:
            public:
                quint32                 flags_;
                CArray<quint16,19*19>   unkown_8; // looks like a lowres version of the height map
                CArray<quint32,4>       texture_ids;
                CArray<quint16,65*65>   texture_blend; // texture maping
                CArray<quint16,65*65>   height_map;
                CArray<quint16,40>      unknown_44EE;
                CArray<quint8,65*65>    shadow_map;
                CArray<quint8,64*64>    unknown_55BF;
                quint8                  unknown_65BE;
                CArray<quint32,4>       unknown_65BF;
                CArray<quint8,0x5344>   unknown_0x04000000;
                CArray<quint8,64*64>    unknown_65CF; // maybe colisions
                CArray<quint32,4>       unknown_75CF;
                CArray<quint16,65*65>   unknown_75DF;
            };
        }
    }
}

#endif // WILDSTAR_DATA_AREA_C_CHUNK_H
