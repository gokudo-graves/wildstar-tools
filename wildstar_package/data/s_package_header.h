#ifndef WILDSTAR_DATA_S_PACKAGE_HEADER_H
#define WILDSTAR_DATA_S_PACKAGE_HEADER_H

#include <QtGlobal>

namespace wildstar
{
    namespace data
    {
        struct SPackageHeader
        {
            enum {
                UNKNOWN_8_COUNT     = 64
              , UNKNOWN_22C_COUNT   = 3
            };

            quint32  magic;
            quint32  version;
            quint64  unkown_008[UNKNOWN_8_COUNT];
            quint64  file_size;
            quint64  unkown_210;
            quint64  block_list_offset;
            quint32  block_count;
            quint32  unkown_224_block_index; // some block index, maybe block_list block index
            quint32  type_block_index;
            quint32  unkown_22C[UNKNOWN_22C_COUNT];
        };

        QDataStream & operator>> (QDataStream& stream, SPackageHeader& header)
        {
            stream >> header.magic >> header.version;
            for( size_t i(0); i < SPackageHeader::UNKNOWN_8_COUNT; ++i )
            {
                stream >> header.unkown_008[i];
            }
            stream >> header.file_size >> header.unkown_210
                   >> header.block_list_offset >> header.block_count
                   >> header.unkown_224_block_index >> header.type_block_index
                   >> header.unkown_210 >> header.block_list_offset
                   ;
            for( size_t i(0); i < SPackageHeader::UNKNOWN_22C_COUNT; ++i )
            {
                stream >> header.unkown_22C[i];
            }

            return stream;
        }
    }
}

#endif // WILDSTAR_DATA_S_PACKAGE_HEADER_H
