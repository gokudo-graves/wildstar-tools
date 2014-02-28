#ifndef C_EXTRACT_COMMAND_H
#define C_EXTRACT_COMMAND_H

#include <QCommandLineOption>

#include "i_command.h"

class CExtractCommand : public ICommand
{
public:
    CExtractCommand();

    virtual void options( QCommandLineParser& parser ) const;
    virtual int execute( QCommandLineParser& parser );

private:
};

#endif // C_EXTRACT_COMMAND_H
