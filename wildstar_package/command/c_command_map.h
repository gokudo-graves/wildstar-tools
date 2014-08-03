#ifndef COMMAND_C_COMMAND_MAP_H
#define COMMAND_C_COMMAND_MAP_H

#include <QMap>

#include "i_command.h"

namespace command {

class CCommandMap : public QMap<QString, ICommand*>
{
public:
    CCommandMap();
    virtual ~CCommandMap();

    virtual void options( QCommandLineParser& parser ) const;
    virtual ICommand* find( QCommandLineParser& parser ) const;
};

}

#endif // COMMAND_C_COMMAND_MAP_H
