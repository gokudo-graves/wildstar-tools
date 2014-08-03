#ifndef COMMAND_C_PATCH_H
#define COMMAND_C_PATCH_H

#include <QCommandLineOption>
#include <QUrl>

#include "c_command_map.h"

namespace command {

class CPatch : public ICommand
{
public:
    CPatch();

    virtual const QString& name() const;
    virtual void options( QCommandLineParser& parser ) const;
    virtual void execute( QSettings& settings, QCommandLineParser& parser );

    virtual const QUrl& baseUrl() const;

private:
    static const QString                NAME;
    static const QCommandLineOption     OPTION_PATCH_SERVER;

    static CCommandMap  createCommands( const CPatch& patch );

    QStringList arguments( const QCommandLineParser& parser ) const;

    const CCommandMap   commands_;
    QUrl    base_url_;
};

}

#endif // COMMAND_C_PATCH_H
