#include <QDebug>

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    parser.setApplicationDescription( app.translate("main", "tool to do some basic actions on wildstar data files") );
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("command", app.translate("main", "the command to execute, use <command> --help for detailed information"), "list|extract");
    parser.process( app );

    try
    {
        return 0;
    }
    catch ( std::exception& e )
    {
        qDebug() << "Exception: " << e.what();
    }

    return 1;
}
