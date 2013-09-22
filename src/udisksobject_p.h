#ifndef UDISKSOBJECT_P_H
#define UDISKSOBJECT_P_H

#include "UDisks.h"

class UDisksDrive;
class UDisksBlock;
class UDisksPartition;
class UDisksObjectPrivate
{
public:
    UDisksObjectPrivate(const QString &path);
    void init(const QVariantMap &properties);

    OrgFreedesktopUDisks2DriveInterface interface;

    UDisksDrive *drive;
    UDisksBlock *block;
    UDisksPartition *partition;
};

#endif // UDISKSOBJECT_P_H
