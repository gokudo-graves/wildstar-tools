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

public slots:
    void version( const QString& version );

private:
    static const QString                NAME;
    static const QCommandLineOption     OPTION_PATCH_SERVER;

    QStringList arguments( const QCommandLineParser& parser ) const;
    CCommandMap createCommands();

    const CCommandMap   commands_;
    QUrl        base_url_;
    QString     version_;
};

}

#endif // COMMAND_C_PATCH_H
