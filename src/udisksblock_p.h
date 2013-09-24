#ifndef UDISKSBLOCK_P_H
#define UDISKSBLOCK_P_H

#include "UDisks.h"

class UDisksBlockPrivate
{
public:
    UDisksBlockPrivate(const QString &path);

    OrgFreedesktopUDisks2BlockInterface interface;
    QVariantMap properties;
};

#endif // UDISKSBLOCK_P_H
