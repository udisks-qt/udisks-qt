#ifndef UDISKSPARTITION_P_H
#define UDISKSPARTITION_P_H

#include "UDisks.h"

class UDisksPartitionPrivate
{
public:
    UDisksPartitionPrivate(const QString &path);

    OrgFreedesktopUDisks2PartitionInterface interface;
    QVariantMap properties;
};

#endif // UDISKSPARTITION_P_H
