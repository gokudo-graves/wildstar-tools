#ifndef COMMAND_C_EXTRACT_H
#define COMMAND_C_EXTRACT_H

#include <QCommandLineOption>

#include "wildstar/data/c_archive.h"
#include "i_command.h"

namespace command
{
    class CExtract : public ICommand
    {
    public:
        CExtract();

        virtual void options( QCommandLineParser& parser ) const;
        virtual int execute( QSettings& settings, QCommandLineParser& parser );

    private:
        virtual int extractDirectory(const wildstar::data::CIndexDirectoryNode* node, QString destination );
        virtual int extractFile( const wildstar::data::CIndexFileNode* node, const QString& destination );

        wildstar::data::CArchive        archive_;
        wildstar::data::CArchiveIndex   index_;

        static const QCommandLineOption     OPTION_FULL_PATH;
    };

}

#endif // COMMAND_C_EXTRACT_H
