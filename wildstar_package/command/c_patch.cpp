#include "command/c_patch.h"

#include "command/patch/c_version.h"

namespace command {

//------------------------------------------------------------------------------
const QString               CPatch::NAME( "patch" );
const QCommandLineOption    CPatch::OPTION_PATCH_SERVER(QStringList() << "b" << "base-url", "the base url of the patch-server");

//------------------------------------------------------------------------------
CCommandMap CPatch::createCommands( const CPatch& patch )
{
    CCommandMap commands;
    commands.add( new patch::CVersion( patch ));
    return commands;
}

//------------------------------------------------------------------------------
CPatch::CPatch() :
    commands_( createCommands( *this ) )
{
}

//------------------------------------------------------------------------------
const QString&
CPatch::name() const
{
    return NAME;
}

//------------------------------------------------------------------------------
void
CPatch::options( QCommandLineParser& parser ) const
{
    parser.addOption( OPTION_PATCH_SERVER );

    parser.addPositionalArgument( NAME, "patch related commands", NAME);

    const QStringList args( arguments( parser ) );
    if( args.isEmpty() )
    {
        commands_.options( parser );
    }

    ICommand* command( commands_.get( parser, args ) );
    command->options( parser );
}

//------------------------------------------------------------------------------
void
CPatch::execute( QSettings& settings, QCommandLineParser& parser )
{
    settings.beginGroup( NAME );
    base_url_ = settings.value( "BaseUrl" ).toUrl();
    settings.endGroup();

    if( parser.isSet( OPTION_PATCH_SERVER ) )
    {
        base_url_ = parser.value( OPTION_PATCH_SERVER );
    }

    ICommand* command( commands_.get( parser, arguments( parser ) ) );
    return command->execute( settings, parser );
}

//------------------------------------------------------------------------------
const QUrl&
CPatch::baseUrl() const
{
    return base_url_;
}

//------------------------------------------------------------------------------
QStringList
CPatch::arguments( const QCommandLineParser& parser ) const
{
    QStringList args( parser.positionalArguments() );
    args.pop_front();
    return args;
}

//------------------------------------------------------------------------------

}
