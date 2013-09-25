#ifndef UDISKSOBJECT_P_H
#define UDISKSOBJECT_P_H

#include "udisksobject.h"
#include "udisksclient.h"

#include <QPointer>

class UDisksObjectPrivate
{
    Q_DECLARE_PUBLIC(UDisksObject)
public:
    UDisksObjectPrivate(const QDBusObjectPath &path, UDisksClient *uDClient, UDisksObject *parent);
    bool _q_addInterface(const QString &interface, const QVariantMap &properties, bool emitSignal);
    bool _q_removeInterface(const QString &interface);
    void _q_propertiesChanged(const QString &interface, const QVariantMap &properties, const QStringList &invalidatedProperties);

    UDisksObject *q_ptr;
    QPointer<UDisksClient> client;
    QDBusObjectPath object;
    UDisksObject::Interfaces interfaces;
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
