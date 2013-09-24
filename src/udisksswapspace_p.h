#ifndef UDISKSSWAPSPACE_P_H
#define UDISKSSWAPSPACE_P_H

#include "UDisks.h"

class UDisksSwapspacePrivate
{
public:
    UDisksSwapspacePrivate(const QString &path);

    OrgFreedesktopUDisks2SwapspaceInterface interface;
    QVariantMap properties;
};

#endif // UDISKSSWAPSPACE_P_H
