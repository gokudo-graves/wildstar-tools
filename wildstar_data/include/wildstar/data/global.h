#ifndef WILDSTAR_DATA_GLOBAL_H
#define WILDSTAR_DATA_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(WILDSTAR_DATA_LIBRARY)
#  define WILDSTAR_DATA_SHARED Q_DECL_EXPORT
#else
#  define WILDSTAR_DATA_SHARED Q_DECL_IMPORT
#endif

#endif // WILDSTAR_DATA_GLOBAL_H
