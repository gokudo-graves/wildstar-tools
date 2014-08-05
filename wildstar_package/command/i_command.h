#ifndef COMMAND_I_COMMAND_H
#define COMMAND_I_COMMAND_H

#include <QCommandLineParser>
#include <QSettings>

namespace command
{

class ICommand : public QObject
{
    Q_OBJECT

public:
    virtual ~ICommand() {}

    virtual const QString& name() const = 0;
    virtual void options( QCommandLineParser& parser ) const = 0;

public slots:
    virtual void execute( QSettings& settings, QCommandLineParser& parser ) = 0;

signals:
    void finished( int code );
};

}

#endif // COMMAND_I_COMMAND_H
