#ifndef UDISKSOBJECT_P_H
#define UDISKSOBJECT_P_H

#include "UDisks.h"

class UDisksDrive;
class UDisksDriveAta;
class UDisksMDRaid;
class UDisksJob;
class UDisksBlock;
class UDisksPartition;
class UDisksPartitionTable;
class UDisksFilesystem;
class UDisksSwapspace;
class UDisksEncrypted;

class UDisksObjectPrivate
{
public:
    UDisksObjectPrivate(const QString &path);
    void init(const QVariantMap &properties);

    OrgFreedesktopUDisks2DriveInterface interface;

    UDisksDrive *drive;
    UDisksDriveAta *driveAta;
    UDisksMDRaid *mDRaid;
    UDisksJob *job;
    UDisksBlock *block;
    UDisksPartition *partition;
    UDisksPartitionTable *partitionTable;
    UDisksFilesystem *filesystem;
    UDisksSwapspace *swapspace;
    UDisksEncrypted *encrypted;
};

#endif // UDISKSOBJECT_P_H
