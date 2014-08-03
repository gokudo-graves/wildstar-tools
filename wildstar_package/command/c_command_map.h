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

    virtual void add( ICommand* command );
    virtual void options( QCommandLineParser& parser ) const;
    virtual ICommand* get( QCommandLineParser& parser ) const;
    virtual ICommand* get( QCommandLineParser& parser, const QStringList args ) const;
};

}

#endif // COMMAND_C_COMMAND_MAP_H
