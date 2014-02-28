#ifndef I_COMMAND_H
#define I_COMMAND_H

#include <QCommandLineParser>

class ICommand
{
public:
    virtual ~ICommand() {}

    virtual void options( QCommandLineParser& parser ) const = 0;
    virtual int execute( QCommandLineParser& parser ) const = 0;
};

#endif // I_COMMAND_H
