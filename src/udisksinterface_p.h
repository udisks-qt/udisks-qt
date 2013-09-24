#ifndef UDISKSINTERFACE_P_H
#define UDISKSINTERFACE_P_H

#include "UDisks.h"

class UDisksInterfacePrivate
{
public:
    UDisksInterfacePrivate(const QString &path);

    QVariantMap properties;
};

#endif // UDISKSINTERFACE_P_H
