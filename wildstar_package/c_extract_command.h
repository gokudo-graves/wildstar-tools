#ifndef C_EXTRACT_COMMAND_H
#define C_EXTRACT_COMMAND_H

//#include <QCommandLineOption>

#include "wildstar/data/c_archive.h"
#include "i_command.h"

class CExtractCommand : public ICommand
{
public:
    CExtractCommand();

    virtual void options( QCommandLineParser& parser ) const;
    virtual int execute( QCommandLineParser& parser );

private:
    virtual void extractBlock( const uint block, const QString& destination, QString file_name = QString() );
    virtual void extractFile( const wildstar::data::CIndexFileNode* file_node, const QString& destination );

    enum ExtractMode {
        BLOCK
      , FILE
      , DIRECTORY
      , UNKNOWN
    };

    wildstar::data::CArchive        archive_;
    wildstar::data::CArchiveIndex   index_;

    //static const QCommandLineOption     OPTION_;
};

#endif // C_EXTRACT_COMMAND_H
