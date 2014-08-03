#include "command/patch/c_version.h"

namespace command {
namespace patch {

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
CVersion::CVersion( const command::CPatch& patch ) :
    patch_( patch )
{
}

//------------------------------------------------------------------------------
void
CVersion::options( QCommandLineParser& parser ) const
{
}

//------------------------------------------------------------------------------
int
CVersion::execute( QSettings& settings, QCommandLineParser& parser )
{
    return 0;
}

//------------------------------------------------------------------------------

}
}
