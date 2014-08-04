#include "command/c_patch.h"

#include "command/patch/c_version.h"

using command::patch::CVersion;

namespace command {

//------------------------------------------------------------------------------
const QString               CPatch::NAME( "patch" );
const QCommandLineOption    CPatch::OPTION_PATCH_SERVER(QStringList() << "b" << "base-url", "the base url of the patch-server");

//------------------------------------------------------------------------------
CPatch::CPatch() :
    commands_( createCommands() )
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
    connect(
        command, &ICommand::finished
      , this   , &ICommand::finished
    );
    command->execute( settings, parser );
}

//------------------------------------------------------------------------------
const QUrl&
CPatch::baseUrl() const
{
    return base_url_;
}

//------------------------------------------------------------------------------
void
CPatch::version( const QString& version )
{
    version_ = version;
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
CCommandMap CPatch::createCommands()
{
    CCommandMap commands;
    CVersion* version( new CVersion( *this ) );

    connect(
        version, &CVersion::version
      , this   , &CPatch::version
    );

    commands.add( version );

    return commands;
}

//------------------------------------------------------------------------------

}
