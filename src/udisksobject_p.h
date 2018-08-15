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
    UDisksObject::Interfaces interfaces = UDisksObject::InterfaceNone;
    UDisksObject::Kind kind = UDisksObject::Unknown;
    UDisksManager *manager = nullptr;
    UDisksDrive *drive = nullptr;
    UDisksDriveAta *driveAta = nullptr;
    UDisksMDRaid *mDRaid = nullptr;
    UDisksJob *job = nullptr;
    UDisksBlock *block = nullptr;
    UDisksPartition *partition = nullptr;
    UDisksPartitionTable *partitionTable = nullptr;
    UDisksFilesystem *filesystem = nullptr;
    UDisksSwapspace *swapspace = nullptr;
    UDisksEncrypted *encrypted = nullptr;
    UDisksLoop *loop = nullptr;
};

#endif // UDISKSOBJECT_P_H
