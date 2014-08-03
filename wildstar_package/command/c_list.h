#ifndef COMMAND_C_LIST_H
#define COMMAND_C_LIST_H

#include <QCommandLineOption>

#include "wildstar/data/c_index_directory_node.h"

#include "i_command.h"

namespace command {

class CList : public ICommand
{
public:
    CList();

    virtual const QString& name() const;
    virtual void options( QCommandLineParser& parser ) const;
    virtual void execute( QSettings& settings, QCommandLineParser& parser );

private:
    virtual void print( const wildstar::data::CIndexDirectoryNode* node, const QString& path = "" ) const;

    bool long_listing_;
    bool show_directories_;

    static const QString                NAME;
    static const QCommandLineOption     OPTION_LONG_LISTING;
    static const QCommandLineOption     OPTION_NO_DIRECTORIES;
};

}

#endif // COMMAND_C_LIST_H
