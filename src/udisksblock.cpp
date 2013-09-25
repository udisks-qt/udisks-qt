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

#include "udisksblock.h"
#include "udisksblock_p.h"

#include "udisksclient.h"
#include "common.h"

#include <QDebug>

UDisksBlock::UDisksBlock(const QDBusObjectPath &objectPath, const QVariantMap &properties, UDisksObject *parent) :
    UDisksInterface(parent),
    d_ptr(new UDisksBlockPrivate(objectPath.path()))
{
    Q_D(UDisksBlock);

    d->properties = properties;
}

UDisksBlock::~UDisksBlock()
{
    delete d_ptr;
}

UDItemList UDisksBlock::configuration() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("Configuration")].value<QList<UDItem> >();
}

QDBusObjectPath UDisksBlock::cryptoBackingDevice() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("CryptoBackingDevice")].value<QDBusObjectPath>();
}

UDisksObject::Ptr UDisksBlock::cryptoBackingDeviceObjectPtr() const
{
    Q_D(const UDisksBlock);
    UDisksObject *object = qobject_cast<UDisksObject*>(parent());
    if (object) {
        UDisksClient *client = object->client();
        if (client) {
            return client->getObject(cryptoBackingDevice());
        }
    }
    return UDisksObject::Ptr();
}

QByteArray UDisksBlock::device() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("Device")].toByteArray();
}

qulonglong UDisksBlock::deviceNumber() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("DeviceNumber")].toULongLong();
}

QDBusObjectPath UDisksBlock::drive() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("Drive")].value<QDBusObjectPath>();
}

UDisksObject::Ptr UDisksBlock::driveObjectPtr() const
{
    Q_D(const UDisksBlock);
    UDisksObject *object = qobject_cast<UDisksObject*>(parent());
    if (object) {
        UDisksClient *client = object->client();
        if (client) {
            return client->getObject(drive());
        }
    }
    return UDisksObject::Ptr();
}

bool UDisksBlock::hintAuto() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("Drive")].toBool();
}

QString UDisksBlock::hintIconName() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("HintIconName")].toString();
}

bool UDisksBlock::hintIgnore() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("HintIgnore")].toBool();
}

QString UDisksBlock::hintName() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("HintName")].toString();
}

bool UDisksBlock::hintPartitionable() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("HintPartitionable")].toBool();
}

QString UDisksBlock::hintSymbolicIconName() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("HintSymbolicIconName")].toString();
}

bool UDisksBlock::hintSystem() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("HintSystem")].toBool();
}

QString UDisksBlock::id() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("Id")].toString();
}

QString UDisksBlock::idLabel() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("IdLabel")].toString();
}

QString UDisksBlock::idType() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("IdType")].toString();
}

QString UDisksBlock::idUUID() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("IdUUID")].toString();
}

QString UDisksBlock::idUsage() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("IdUsage")].toString();
}

QString UDisksBlock::idVersion() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("IdVersion")].toString();
}

QDBusObjectPath UDisksBlock::mDRaid() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("MDRaid")].value<QDBusObjectPath>();
}

UDisksObject::Ptr UDisksBlock::mDRaidObjectPtr() const
{
    Q_D(const UDisksBlock);
    UDisksObject *object = qobject_cast<UDisksObject*>(parent());
    if (object) {
        UDisksClient *client = object->client();
        if (client) {
            return client->getObject(mDRaid());
        }
    }
    return UDisksObject::Ptr();
}

QDBusObjectPath UDisksBlock::mDRaidMember() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("MDRaidMember")].value<QDBusObjectPath>();
}

UDisksObject::Ptr UDisksBlock::mDRaidMemberObjectPtr() const
{
    Q_D(const UDisksBlock);
    UDisksObject *object = qobject_cast<UDisksObject*>(parent());
    if (object) {
        UDisksClient *client = object->client();
        if (client) {
            return client->getObject(mDRaidMember());
        }
    }
    return UDisksObject::Ptr();
}

QByteArray UDisksBlock::preferredDevice() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("PreferredDevice")].toByteArray();
}

bool UDisksBlock::readOnly() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("ReadOnly")].toBool();
}

qulonglong UDisksBlock::size() const
{
    Q_D(const UDisksBlock);
    return d->properties[QLatin1String("Size")].toULongLong();
}

QStringList UDisksBlock::symlinks() const
{
    Q_D(const UDisksBlock);
    QStringList ret;
    QVariant variant = d->properties[QLatin1String("Symlinks")];
    UDByteArrayList symlinks = qdbus_cast<UDByteArrayList>(variant);
    foreach (const QByteArray &symlink, symlinks) {
        ret << QFile::decodeName(symlink);
    }
    return ret;
}

QDBusPendingReply<> UDisksBlock::addConfigurationItem(UDItem item, const QVariantMap &options)
{
    Q_D(UDisksBlock);
    return d->interface.AddConfigurationItem(item, options);
}

QDBusPendingReply<> UDisksBlock::format(const QString &type, const QVariantMap &options)
{
    Q_D(UDisksBlock);
    return d->interface.Format(type, options);
}

QDBusPendingReply<QList<QVariantMap> > UDisksBlock::getSecretConfiguration(const QVariantMap &options)
{
    Q_D(UDisksBlock);
    return d->interface.GetSecretConfiguration(options);
}

QDBusPendingReply<QDBusUnixFileDescriptor> UDisksBlock::openForBackup(const QVariantMap &options)
{
    Q_D(UDisksBlock);
    return d->interface.OpenForBackup(options);
}

QDBusPendingReply<QDBusUnixFileDescriptor> UDisksBlock::openForBenchmark(const QVariantMap &options)
{
    Q_D(UDisksBlock);
    return d->interface.OpenForBenchmark(options);
}

QDBusPendingReply<QDBusUnixFileDescriptor> UDisksBlock::openForRestore(const QVariantMap &options)
{
    Q_D(UDisksBlock);
    return d->interface.OpenForRestore(options);
}

QDBusPendingReply<> UDisksBlock::removeConfigurationItem(UDItem item, const QVariantMap &options)
{
    Q_D(UDisksBlock);
    return d->interface.RemoveConfigurationItem(item, options);
}

QDBusPendingReply<> UDisksBlock::rescan(const QVariantMap &options)
{
    Q_D(UDisksBlock);
    return d->interface.Rescan(options);
}

QDBusPendingReply<> UDisksBlock::updateConfigurationItem(UDItem oldItem, UDItem newItem, const QVariantMap &options)
{
    Q_D(UDisksBlock);
    return d->interface.UpdateConfigurationItem(oldItem, newItem, options);
}

void UDisksBlock::propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties)
{
    Q_D(UDisksBlock);
    changeProperties(d->properties, properties, invalidProperties);
}

UDisksBlockPrivate::UDisksBlockPrivate(const QString &path) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus())
{
}
