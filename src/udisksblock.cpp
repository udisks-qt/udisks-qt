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

#include "common.h"

#include <QDebug>

UDisksBlock::UDisksBlock(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties, QObject *parent) :
    QObject(parent),
    d_ptr(new UDisksBlockPrivate(objectPath.path()))
{
    Q_D(UDisksBlock);

    UDVariantMapMap::ConstIterator it = interfacesAndProperties.constBegin();
    while (it != interfacesAndProperties.constEnd()) {
        const QString &interface = it.key();
        if (interface == QLatin1String(UD2_INTERFACE_BLOCK)) {
            d->init(it.value());
        } else {
            qWarning() << Q_FUNC_INFO << "Unknown interface, please report a bug:" << interface;
        }

        ++it;
    }
}

QList<UDItem> UDisksBlock::configuration() const
{
    Q_D(const UDisksBlock);
    return d->configuration;
}

QDBusObjectPath UDisksBlock::cryptoBackingDevice() const
{
    Q_D(const UDisksBlock);
    return d->cryptoBackingDevice;
}

QByteArray UDisksBlock::device() const
{
    Q_D(const UDisksBlock);
    return d->device;
}

qulonglong UDisksBlock::deviceNumber() const
{
    Q_D(const UDisksBlock);
    return d->deviceNumber;
}

QDBusObjectPath UDisksBlock::drive() const
{
    Q_D(const UDisksBlock);
    return d->drive;
}

bool UDisksBlock::hintAuto() const
{
    Q_D(const UDisksBlock);
    return d->hintAuto;
}

QString UDisksBlock::hintIconName() const
{
    Q_D(const UDisksBlock);
    return d->hintIconName;
}

bool UDisksBlock::hintIgnore() const
{
    Q_D(const UDisksBlock);
    return d->hintIgnore;
}

QString UDisksBlock::hintName() const
{
    Q_D(const UDisksBlock);
    return d->hintName;
}

bool UDisksBlock::hintPartitionable() const
{
    Q_D(const UDisksBlock);
    return d->hintPartitionable;
}

QString UDisksBlock::hintSymbolicIconName() const
{
    Q_D(const UDisksBlock);
    return d->hintSymbolicIconName;
}

bool UDisksBlock::hintSystem() const
{
    Q_D(const UDisksBlock);
    return d->hintSystem;
}

QString UDisksBlock::id() const
{
    Q_D(const UDisksBlock);
    return d->id;
}

QString UDisksBlock::idLabel() const
{
    Q_D(const UDisksBlock);
    return d->idLabel;
}

QString UDisksBlock::idType() const
{
    Q_D(const UDisksBlock);
    return d->idType;
}

QString UDisksBlock::idUUID() const
{
    Q_D(const UDisksBlock);
    return d->idUUID;
}

QString UDisksBlock::idUsage() const
{
    Q_D(const UDisksBlock);
    return d->idUsage;
}

QString UDisksBlock::idVersion() const
{
    Q_D(const UDisksBlock);
    return d->idVersion;
}

QDBusObjectPath UDisksBlock::mDRaid() const
{
    Q_D(const UDisksBlock);
    return d->mDRaid;
}

QDBusObjectPath UDisksBlock::mDRaidMember() const
{
    Q_D(const UDisksBlock);
    return d->mDRaidMember;
}

QByteArray UDisksBlock::preferredDevice() const
{
    Q_D(const UDisksBlock);
    return d->preferredDevice;
}

bool UDisksBlock::readOnly() const
{
    Q_D(const UDisksBlock);
    return d->readOnly;
}

qulonglong UDisksBlock::size() const
{
    Q_D(const UDisksBlock);
    return d->size;
}

QList<QByteArray> UDisksBlock::symlinks() const
{
    Q_D(const UDisksBlock);
    return d->symlinks;
}

UDisksBlockPrivate::UDisksBlockPrivate(const QString &path) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus())
{
}

void UDisksBlockPrivate::init(const QVariantMap &properties)
{
    QVariantMap::ConstIterator it = properties.constBegin();
    while (it != properties.constEnd()) {
        const QString &property = it.key();
        const QVariant &value = it.value();
        qDebug() << Q_FUNC_INFO << property << value;

        if (property == QLatin1String("Configuration")) {
            configuration = value.value<QList<UDItem> >();
        } else if (property == QLatin1String("CryptoBackingDevice")) {
            cryptoBackingDevice = value.value<QDBusObjectPath>();
        } else if (property == QLatin1String("Device")) {
            device = value.toByteArray();
        } else if (property == QLatin1String("DeviceNumber")) {
            deviceNumber = value.toULongLong();
        } else if (property == QLatin1String("Drive")) {
            drive = value.value<QDBusObjectPath>();
        } else if (property == QLatin1String("HintAuto")) {
            hintAuto = value.toBool();
        } else if (property == QLatin1String("HintIconName")) {
            hintIconName = value.toString();
        } else if (property == QLatin1String("HintIgnore")) {
            hintIgnore = value.toBool();
        } else if (property == QLatin1String("HintName")) {
            hintName = value.toString();
        } else if (property == QLatin1String("HintPartitionable")) {
            hintPartitionable = value.toBool();
        } else if (property == QLatin1String("HintSymbolicIconName")) {
            hintSymbolicIconName = value.toString();
        } else if (property == QLatin1String("HintSystem")) {
            hintSystem = value.toBool();
        } else if (property == QLatin1String("Id")) {
            id = value.toString();
        } else if (property == QLatin1String("IdLabel")) {
            idLabel = value.toString();
        } else if (property == QLatin1String("IdType")) {
            idType = value.toString();
        } else if (property == QLatin1String("IdUUID")) {
            idUUID = value.toString();
        } else if (property == QLatin1String("IdUsage")) {
            idUsage = value.toString();
        } else if (property == QLatin1String("IdVersion")) {
            idVersion = value.toString();
        } else if (property == QLatin1String("MDRaid")) {
            mDRaid = value.value<QDBusObjectPath>();
        } else if (property == QLatin1String("MDRaidMember")) {
            mDRaidMember = value.value<QDBusObjectPath>();
        } else if (property == QLatin1String("PreferredDevice")) {
            preferredDevice = value.toByteArray();
        } else if (property == QLatin1String("ReadOnly")) {
            readOnly = value.toBool();
        } else if (property == QLatin1String("Size")) {
            size = value.toULongLong();
        } else if (property == QLatin1String("Symlinks")) {
            symlinks = value.value<QList<QByteArray> >();
        } else {
            qWarning() << Q_FUNC_INFO << "Unknown property, please report a bug:" << property << value;
        }

        ++it;
    }
}
