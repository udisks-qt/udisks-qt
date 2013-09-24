#ifndef UDISKSMDRAID_P_H
#define UDISKSMDRAID_P_H

#include "UDisks.h"

class UDisksMDRaidPrivate
{
public:
    UDisksMDRaidPrivate(const QString &path);

    OrgFreedesktopUDisks2MDRaidInterface interface;
    QVariantMap properties;
};

#endif // UDISKSMDRAID_P_H
