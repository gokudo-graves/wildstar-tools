#include "wildstar/data/c_package.h"

#include <cstring>
#include <QDataStream>

#include "wildstar/data/exception.h"

namespace wildstar
{
    namespace data
    {
        //----------------------------------------------------------------------
        CPackage::CPackage( const QString& file_name ) :
            file_( file_name )
        {
            clear();
        }

        //----------------------------------------------------------------------
        void
        CPackage::open( const QString& file_name )
        {
            if( !file_name.isNull() )
            {
                file_.close();
                file_.setFileName( file_name );
            }
            clear();
            checkFile();

            loadHeader();
            checkHeader();

            loadBlocks();
            checkBlocks();
        }

        //----------------------------------------------------------------------
        quint32
        CPackage::getBlockCount() const
        {
            return header_.block_count;
        }

        //----------------------------------------------------------------------
        QByteArray
        CPackage::read( qint64 offset, qint64 bytes )
        {
            file_.seek( offset );
            return file_.read( bytes );
        }

        //----------------------------------------------------------------------
        QByteArray
        CPackage::readBlock( quint32 index )
        {
            const BlockDescription& block( blocks_[index] );
            return read( block.offset, block.size );
        }

        //----------------------------------------------------------------------
        QByteArray
        CPackage::readTypeBlock()
        {
            return readBlock( header_.type_block_index );
        }

        //----------------------------------------------------------------------
        void
        CPackage::clear()
        {
            std::memset( &header_, 0, sizeof( header_) );
            blocks_.clear();
        }

        //----------------------------------------------------------------------
        void
        CPackage::loadHeader()
        {
            QDataStream stream( read( 0, HEADER_SIZE ) );
            stream.setByteOrder( QDataStream::LittleEndian );
            stream >> header_;
        }

        //----------------------------------------------------------------------
        void
        CPackage::loadBlocks()
        {
            qint64 offset( header_.block_descriptions_offset );
            qint64 size( header_.block_count * BLOCK_DESCRIPTION_SIZE );
            QDataStream stream( read( offset, size ) );
            stream.setByteOrder( QDataStream::LittleEndian );

            for( quint32 i(0); i < header_.block_count; ++i )
            {
                BlockDescription block;
                stream >> block;
                blocks_.push_back( block );
            }
        }

        //----------------------------------------------------------------------
        void
        CPackage::checkFile()
        {
            if( !file_.exists() )
            {
                throw EInvalidFileNotExist();
            }

            if( file_.size() < sizeof(header_) )
            {
                throw EInvalidFileSize();
            }

            if( !file_.isOpen() && !file_.open( QIODevice::ReadOnly ) )
            {
                throw EInvalidFileNotReadable();
            }
        }

        //----------------------------------------------------------------------
        void
        CPackage::checkHeader() const
        {
            if( header_.magic != MAGIC )
            {
                throw EInvalidFileSignature();
            }

            if( header_.version != VERSION )
            {
                throw EInvalidFileVersion();
            }

            if(    ( header_.file_size > file_.size() )
                || ( header_.block_descriptions_offset & 0xF )
                || ( header_.block_descriptions_offset > header_.file_size )
                || ( header_.type_block_index >= header_.block_count )
                || ( header_.unkown_224_block_index >= header_.block_count )
              )
            {
                throw EInvalidFileHeader();
            }
        }

        //----------------------------------------------------------------------
        void
        CPackage::checkBlocks() const
        {
            for( quint32 i(0); i < header_.block_count; ++i )
            {
                const BlockDescription& block( blocks_[i] );

                if( block.size )
                {
                    if(    ( block.offset & 0xF )
                        || ( block.offset < MINIMUM_BLOCK_OFFSET )
                        || ( block.offset > header_.file_size )
                        || ( block.offset + block.size > header_.file_size )
                      )
                    {
                        throw EInvalidFileHeader();
                    }
                }
            }
        }

        //----------------------------------------------------------------------
        QDataStream&
        operator>>( QDataStream& stream, CPackage::Header& header )
        {
            stream >> header.magic >> header.version;
            for( size_t i(0); i <  CPackage::Header::UNKNOWN_8_COUNT; ++i )
            {
                stream >> header.unkown_008[i];
            }
            stream >> header.file_size >> header.unkown_210
                   >> header.block_descriptions_offset >> header.block_count
                   >> header.unkown_224_block_index >> header.type_block_index
                   ;

            return stream;
        }

        //----------------------------------------------------------------------
        QDataStream&
        operator>>( QDataStream& stream, CPackage::BlockDescription& block )
        {
            stream >> block.offset >> block.size;

            return stream;
        }

        //----------------------------------------------------------------------
    }
}
