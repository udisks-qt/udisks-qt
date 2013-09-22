#ifndef UDISKSOBJECT_P_H
#define UDISKSOBJECT_P_H

#include "UDisks.h"

class UDisksDrive;
class UDisksDriveAta;
class UDisksBlock;
class UDisksPartition;
class UDisksPartitionTable;

class UDisksObjectPrivate
{
public:
    UDisksObjectPrivate(const QString &path);
    void init(const QVariantMap &properties);

    OrgFreedesktopUDisks2DriveInterface interface;

    UDisksDrive *drive;
    UDisksDriveAta *driveAta;
    UDisksBlock *block;
    UDisksPartition *partition;
    UDisksPartitionTable *partitionTable;
};

#endif // UDISKSOBJECT_P_H
