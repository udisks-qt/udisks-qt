#ifndef UDISKSDEFS_H
#define UDISKSDEFS_H

#include <QtCore/qglobal.h>

#ifndef UDISKS_STATIC
#    if defined(QT_BUILD_MULTIMEDIA_LIB)
#        define UDISKS_EXPORT Q_DECL_EXPORT
#    else
#        define UDISKS_EXPORT Q_DECL_IMPORT
#    endif
#else
#    define UDISKS_EXPORT
#endif

#endif // UDISKSDEFS_H
