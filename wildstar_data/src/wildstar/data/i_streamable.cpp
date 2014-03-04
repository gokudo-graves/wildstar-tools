#include "wildstar/data/i_streamable.h"

namespace wildstar
{
    namespace data
    {
        QDataStream& operator>>( QDataStream& stream, IStreamable& data )
        {
            data.read( stream );
            return stream;
        }
    }
}
