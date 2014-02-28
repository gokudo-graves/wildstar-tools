#ifndef C_LIST_COMMAND_H
#define C_LIST_COMMAND_H

#include <QCommandLineOption>

#include "wildstar/data/c_index_directory_node.h"

#include "i_command.h"

class CListCommand : public ICommand
{
public:
    CListCommand();

    virtual void options( QCommandLineParser& parser ) const;
    virtual int execute( QCommandLineParser& parser );

private:
    virtual void print( const wildstar::data::CIndexDirectoryNode* node, const QString& path = "" ) const;

    bool long_listing_;
    bool show_directories_;

    static const QCommandLineOption     OPTION_LONG_LISTING;
    static const QCommandLineOption     OPTION_NO_DIRECTORIES;
};

#endif // C_LIST_COMMAND_H
