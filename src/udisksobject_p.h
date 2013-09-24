#ifndef UDISKSOBJECT_P_H
#define UDISKSOBJECT_P_H

#include "udisksobject.h"

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
class UDisksLoop;

class UDisksObjectPrivate
{
public:
    UDisksObjectPrivate(const QDBusObjectPath &path);

    QDBusObjectPath object;
    UDisksObject::Kind kind;
    UDisksManager *manager;
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
    UDisksLoop *loop;
};

#endif // UDISKSOBJECT_P_H
