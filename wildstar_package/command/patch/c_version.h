#ifndef COMMAND_PATCH_C_VERSION_H
#define COMMAND_PATCH_C_VERSION_H

#include "QNetworkAccessManager"

#include "../c_patch.h"

namespace command {
namespace patch {

class CVersion : public ICommand
{
public:
    explicit CVersion( const command::CPatch& patch );

    virtual const QString& name() const;
    virtual void options( QCommandLineParser& parser ) const;
    virtual void execute( QSettings& settings, QCommandLineParser& parser );

private:
    static const QString                NAME;
    static const QUrl                   VERSION_FILE;

    const command::CPatch& patch_;
    QNetworkAccessManager qnam_;
};

}
}

#endif // COMMAND_PATCH_C_VERSION_H
