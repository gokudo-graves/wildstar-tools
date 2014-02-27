#ifndef WS_DATA_C_PACKAGE_H
#define WS_DATA_C_PACKAGE_H

#include <QFile>

namespace ws
{
    namespace data
    {
        class CPackage
        {
        public:
            CPackage();

        private:
            QFile file_;
        };
    }
}
#endif // WS_DATA_C_PACKAGE_H
