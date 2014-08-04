#ifndef COMMAND_PATCH_C_VERSION_H
#define COMMAND_PATCH_C_VERSION_H

#include "QNetworkAccessManager"
#include "QNetworkReply"

#include "../c_patch.h"

namespace command {
namespace patch {

class CVersion : public ICommand
{
    Q_OBJECT

public:
    explicit CVersion( const CPatch& patch );

    virtual const QString& name() const;
    virtual void options( QCommandLineParser& parser ) const;
    virtual void execute( QSettings& settings, QCommandLineParser& parser );

signals:
    void version( const QString& version );

public slots:
    void onReply( QNetworkReply* reply );

private:
    static const QString                NAME;
    static const QUrl                   VERSION_FILE;

    const command::CPatch& patch_;
    QNetworkAccessManager qnam_;
};

}
}

#endif // COMMAND_PATCH_C_VERSION_H
