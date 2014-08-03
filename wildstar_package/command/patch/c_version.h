#ifndef COMMAND_PATCH_C_VERSION_H
#define COMMAND_PATCH_C_VERSION_H

#include "../c_patch.h"

namespace command {
namespace patch {

class CVersion : public ICommand
{
public:
    explicit CVersion( const command::CPatch& patch );

    virtual void options( QCommandLineParser& parser ) const;
    virtual int execute( QSettings& settings, QCommandLineParser& parser );

private:
    const command::CPatch& patch_;
};

}
}

#endif // COMMAND_PATCH_C_VERSION_H
