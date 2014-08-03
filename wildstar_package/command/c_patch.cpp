#include "command/c_patch.h"

namespace command {

//------------------------------------------------------------------------------
const QCommandLineOption    CPatch::OPTION_PATCH_SERVER(QStringList() << "b" << "base-url", "the base url of the patch-server");

//------------------------------------------------------------------------------
CPatch::CPatch()
{
}

//------------------------------------------------------------------------------
void
CPatch::options( QCommandLineParser& parser ) const
{
    parser.addOption( OPTION_PATCH_SERVER );

    parser.addPositionalArgument("list", "list files and directories in an index file", "list");

    QStringList args( parser.positionalArguments() );
    args.pop_front();
    ICommand command( commands_.find( parser, .pop_front(); ) );
}

//------------------------------------------------------------------------------
int
CPatch::execute( QSettings& settings, QCommandLineParser& parser )
{
    settings.beginGroup( "Patch" );
    base_url_ = settings.value( "BaseUrl" ).toUrl();
    settings.endGroup();

    if( parser.isSet( OPTION_PATCH_SERVER ) )
    {
        base_url_ = parser.value( OPTION_PATCH_SERVER );
    }

    if( base_url_.isEmpty() )
    {
        qWarning() << "base-url not set.\n";
        return 1;
    }
    return 0;
}

//------------------------------------------------------------------------------

}
