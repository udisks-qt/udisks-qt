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
    Q_DECLARE_PUBLIC(UDisksObject)
public:
    UDisksObjectPrivate(const QDBusObjectPath &path, UDisksObject *parent);
    bool _q_addInterface(const QString &interface, const QVariantMap &properties, bool emitSignal);
    bool _q_removeInterface(const QString &interface);

    UDisksObject *q_ptr;
    QDBusObjectPath object;
    QStringList interfaces;
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
