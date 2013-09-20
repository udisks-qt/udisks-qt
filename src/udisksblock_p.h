#ifndef UDISKSBLOCK_P_H
#define UDISKSBLOCK_P_H

#include "UDisks.h"

class UDisksBlockPrivate
{
public:
    UDisksBlockPrivate(const QString &path);
    void init(const QVariantMap &properties);

    OrgFreedesktopUDisks2BlockInterface interface;

    QList<UDItem> configuration;
    QDBusObjectPath cryptoBackingDevice;
    QByteArray device;
    qulonglong deviceNumber;
    QDBusObjectPath drive;
    bool hintAuto;
    QString hintIconName;
    bool hintIgnore;
    QString hintName;
    bool hintPartitionable;
    QString hintSymbolicIconName;
    bool hintSystem;
    QString id;
    QString idLabel;
    QString idType;
    QString idUUID;
    QString idUsage;
    QString idVersion;
    QDBusObjectPath mDRaid;
    QDBusObjectPath mDRaidMember;
    QByteArray preferredDevice;
    bool readOnly;
    qulonglong size;
    QList<QByteArray> symlinks;
};

#endif // UDISKSBLOCK_P_H
