#ifndef UDISKSPARTITIONTABLE_P_H
#define UDISKSPARTITIONTABLE_P_H

#include "UDisks.h"

class UDisksPartitionTablePrivate
{
public:
    UDisksPartitionTablePrivate(const QString &path);
    void init(const QVariantMap &properties);

    OrgFreedesktopUDisks2PartitionTableInterface interface;

    QString type;
};

#endif // UDISKSPARTITIONTABLE_P_H
