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

    virtual void options( QCommandLineParser& parser ) const;
    virtual int execute( QSettings& settings, QCommandLineParser& parser );

private:
    static const QCommandLineOption     OPTION_PATCH_SERVER;

    const CCommandMap   commands_;
    QUrl    base_url_;
};

}

#endif // COMMAND_C_PATCH_H
