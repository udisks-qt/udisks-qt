#ifndef UDISKSPARTITIONTABLE_P_H
#define UDISKSPARTITIONTABLE_P_H

#include "UDisks.h"

class UDisksPartitionTablePrivate
{
public:
    UDisksPartitionTablePrivate(const QString &path);

    OrgFreedesktopUDisks2PartitionTableInterface interface;
    QVariantMap properties;
};

#endif // UDISKSPARTITIONTABLE_P_H
