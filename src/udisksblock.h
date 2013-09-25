/*
 * Copyright (C) 2013 Daniel Nicoletti <dantti12@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef UDISKSBLOCK_H
#define UDISKSBLOCK_H

#include <QObject>
#include <QtDBus/QDBusUnixFileDescriptor>
#include <QtDBus/QDBusPendingReply>

#include "udisksinterface.h"
#include "udisksobject.h"
#include "dbus-types.h"

class UDisksBlockPrivate;
class UDisksBlock : public UDisksInterface
{
    Q_OBJECT
public:
    explicit UDisksBlock(const QDBusObjectPath &objectPath, const QVariantMap &properties, UDisksObject *parent);
    ~UDisksBlock();

    Q_PROPERTY(UDItemList configuration READ configuration)
    UDItemList configuration() const;

    Q_PROPERTY(QDBusObjectPath cryptoBackingDevice READ cryptoBackingDevice)
    QDBusObjectPath cryptoBackingDevice() const;

    UDisksObject::Ptr cryptoBackingDeviceObjectPtr() const;

    Q_PROPERTY(QByteArray device READ device)
    QByteArray device() const;

    Q_PROPERTY(qulonglong deviceNumber READ deviceNumber)
    qulonglong deviceNumber() const;

    Q_PROPERTY(QDBusObjectPath drive READ drive)
    QDBusObjectPath drive() const;

    UDisksObject::Ptr driveObjectPtr() const;

    Q_PROPERTY(bool hintAuto READ hintAuto)
    bool hintAuto() const;

    Q_PROPERTY(QString hintIconName READ hintIconName)
    QString hintIconName() const;

    Q_PROPERTY(bool hintIgnore READ hintIgnore)
    bool hintIgnore() const;

    Q_PROPERTY(QString hintName READ hintName)
    QString hintName() const;

    Q_PROPERTY(bool hintPartitionable READ hintPartitionable)
    bool hintPartitionable() const;

    Q_PROPERTY(QString hintSymbolicIconName READ hintSymbolicIconName)
    QString hintSymbolicIconName() const;

    Q_PROPERTY(bool hintSystem READ hintSystem)
    bool hintSystem() const;

    Q_PROPERTY(QString blockId READ id)
    QString id() const;

    Q_PROPERTY(QString idLabel READ idLabel)
    QString idLabel() const;

    Q_PROPERTY(QString idType READ idType)
    QString idType() const;

    Q_PROPERTY(QString idUUID READ idUUID)
    QString idUUID() const;

    Q_PROPERTY(QString idUsage READ idUsage)
    QString idUsage() const;

    Q_PROPERTY(QString idVersion READ idVersion)
    QString idVersion() const;

    Q_PROPERTY(QDBusObjectPath mDRaid READ mDRaid)
    QDBusObjectPath mDRaid() const;

    UDisksObject::Ptr mDRaidObjectPtr() const;

    Q_PROPERTY(QDBusObjectPath mDRaidMember READ mDRaidMember)
    QDBusObjectPath mDRaidMember() const;

    UDisksObject::Ptr mDRaidMemberObjectPtr() const;

    Q_PROPERTY(QByteArray preferredDevice READ preferredDevice)
    QByteArray preferredDevice() const;

    Q_PROPERTY(bool readOnly READ readOnly)
    bool readOnly() const;

    Q_PROPERTY(qulonglong size READ size)
    qulonglong size() const;

    Q_PROPERTY(QStringList symlinks READ symlinks)
    QStringList symlinks() const;

public Q_SLOTS:
    QDBusPendingReply<> addConfigurationItem(UDItem item, const QVariantMap &options = QVariantMap());

    QDBusPendingReply<> format(const QString &type, const QVariantMap &options = QVariantMap());

    QDBusPendingReply<QList<QVariantMap> > getSecretConfiguration(const QVariantMap &options = QVariantMap());

    QDBusPendingReply<QDBusUnixFileDescriptor> openForBackup(const QVariantMap &options = QVariantMap());

    QDBusPendingReply<QDBusUnixFileDescriptor> openForBenchmark(const QVariantMap &options = QVariantMap());

    QDBusPendingReply<QDBusUnixFileDescriptor> openForRestore(const QVariantMap &options = QVariantMap());

    QDBusPendingReply<> removeConfigurationItem(UDItem item, const QVariantMap &options = QVariantMap());

    QDBusPendingReply<> rescan(const QVariantMap &options = QVariantMap());

    QDBusPendingReply<> updateConfigurationItem(UDItem oldItem, UDItem newItem, const QVariantMap &options = QVariantMap());

protected:
    virtual void propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties);
    UDisksBlockPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksBlock)
};

#endif // UDISKSBLOCK_H
