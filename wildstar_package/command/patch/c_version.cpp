#include "command/patch/c_version.h"

#include "QDebug"

#include "QNetworkRequest"

namespace command {
namespace patch {

//------------------------------------------------------------------------------
const QString               CVersion::NAME( "version" );
const QUrl                  CVersion::VERSION_FILE( "version.txt" );

//------------------------------------------------------------------------------
CVersion::CVersion( const CPatch& patch ) :
    patch_( patch )
{
    connect(
        &qnam_, &QNetworkAccessManager::finished
      , this  , &CVersion::onReply
    );
}

//------------------------------------------------------------------------------
const QString&
CVersion::name() const
{
    return NAME;
}

//------------------------------------------------------------------------------
void
CVersion::options( QCommandLineParser& parser ) const
{
    parser.addPositionalArgument( NAME, "query the current version of the patch-server", NAME);
}

//------------------------------------------------------------------------------
void
CVersion::execute( QSettings&, QCommandLineParser& )
{
    const QUrl& base_url( patch_.baseUrl() );
    if( base_url.isEmpty() )
    {
        qWarning() << "base url not set.\n";
        emit finished( 1 );
        return;
    }
    QUrl version_file( base_url.resolved( VERSION_FILE ) );
    qnam_.get( QNetworkRequest( version_file ) );
}

//------------------------------------------------------------------------------
void
CVersion::onReply( QNetworkReply* reply )
{
    const QString version_text( reply->readAll() );
    qDebug() << version_text;
    emit version( version_text );
    emit finished( 0 );
}

//------------------------------------------------------------------------------

}
}
