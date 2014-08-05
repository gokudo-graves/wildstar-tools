#ifndef C_APPLICATION_H
#define C_APPLICATION_H

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QSettings>

class CApplication : public QCoreApplication
{
    Q_OBJECT
public:
    CApplication( int &argc, char **argv );

signals:
    void started( QSettings& settings, QCommandLineParser& parser );

public slots:
};

#endif // C_APPLICATION_H
