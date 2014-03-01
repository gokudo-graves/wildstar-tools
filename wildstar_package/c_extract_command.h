#ifndef C_EXTRACT_COMMAND_H
#define C_EXTRACT_COMMAND_H

#include <QCommandLineOption>

#include "wildstar/data/c_archive.h"
#include "i_command.h"

class CExtractCommand : public ICommand
{
public:
    CExtractCommand();

    virtual void options( QCommandLineParser& parser ) const;
    virtual int execute( QCommandLineParser& parser );

private:
    virtual int extractDirectory(const wildstar::data::CIndexDirectoryNode* node, QString destination );
    virtual int extractFile( const wildstar::data::CIndexFileNode* node, const QString& destination );

    wildstar::data::CArchive        archive_;
    wildstar::data::CArchiveIndex   index_;

    static const QCommandLineOption     OPTION_FULL_PATH;
};

#endif // C_EXTRACT_COMMAND_H
