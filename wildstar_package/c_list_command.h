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

    static const QCommandLineOption     SUB_FOLDER_OPTION;
    static const QCommandLineOption     LONG_LISTING_OPTION;
};

#endif // C_LIST_COMMAND_H
