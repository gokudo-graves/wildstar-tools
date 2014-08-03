#ifndef COMMAND_I_COMMAND_H
#define COMMAND_I_COMMAND_H

#include <QCommandLineParser>
#include <QSettings>

namespace command
{
    class ICommand
    {
    public:
        virtual ~ICommand() {}

        virtual void options( QCommandLineParser& parser ) const = 0;
        virtual int execute( QSettings& settings, QCommandLineParser& parser ) = 0;
    };
}

#endif // COMMAND_I_COMMAND_H
