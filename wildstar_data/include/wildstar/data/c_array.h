#ifndef WILDSTAR_DATA_C_ARRAY_H
#define WILDSTAR_DATA_C_ARRAY_H

#include <cstring>

#include "global.h"

#include "i_streamable.h"

namespace wildstar
{
    namespace data
    {
        template<typename TValueType, int SIZE>
        class WILDSTAR_DATA_SHARED CArray : public IStreamable
        {
        public:
            //----------------------------------------------------------------------
            CArray()
            {
                clear();
            }

            //----------------------------------------------------------------------
            virtual ~CArray(){}

            //----------------------------------------------------------------------
            virtual void clear()
            {
                std::memset( &data_, 0, sizeof( data_ ) );
            }

            //----------------------------------------------------------------------
            virtual void read( QDataStream& stream )
            {
                for( int i(0); i < SIZE; ++i )
                {
                    stream >> data_[i];
                }
            }

            //----------------------------------------------------------------------
            virtual const TValueType& operator[]( const size_t& index ) const
            {
                return data_[index];
            }

            //----------------------------------------------------------------------
            virtual const TValueType* data() const
            {
                return data_;
            }

            //----------------------------------------------------------------------

        protected:

        private:
            TValueType data_[SIZE];
        };
    }
}
#endif // WILDSTAR_DATA_C_ARRAY_H
