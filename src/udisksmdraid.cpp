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

#include "udisksmdraid.h"
#include "udisksmdraid_p.h"

#include "common.h"

#include <QDebug>

UDisksMDRaid::UDisksMDRaid(const QDBusObjectPath &objectPath, const QVariantMap &properties, UDisksObject *parent) :
    UDisksInterface(parent),
    d_ptr(new UDisksMDRaidPrivate(objectPath.path()))
{
    Q_D(UDisksMDRaid);

    d->properties = properties;
}

UDisksMDRaid::~UDisksMDRaid()
{
    delete d_ptr;
}

UDisksActiveDevice UDisksMDRaid::activeDevices() const
{
    Q_D(const UDisksMDRaid);
    return d->properties.value(QStringLiteral("ActiveDevices")).value<UDisksActiveDevice>();
}

QByteArray UDisksMDRaid::bitmapLocation() const
{
    Q_D(const UDisksMDRaid);
    return d->properties.value(QStringLiteral("BitmapLocation")).toByteArray();
}

qulonglong UDisksMDRaid::chunkSize() const
{
    Q_D(const UDisksMDRaid);
    return d->properties.value(QStringLiteral("ChunkSize")).toULongLong();
}

uint UDisksMDRaid::degraded() const
{
    Q_D(const UDisksMDRaid);
    return d->properties.value(QStringLiteral("Degraded")).toUInt();
}

QString UDisksMDRaid::level() const
{
    Q_D(const UDisksMDRaid);
    return d->properties.value(QStringLiteral("Level")).toString();
}

QString UDisksMDRaid::name() const
{
    Q_D(const UDisksMDRaid);
    return d->properties.value(QStringLiteral("Name")).toString();
}

uint UDisksMDRaid::numDevices() const
{
    Q_D(const UDisksMDRaid);
    return d->properties.value(QStringLiteral("NumDevices")).toUInt();
}

qulonglong UDisksMDRaid::size() const
{
    Q_D(const UDisksMDRaid);
    return d->properties.value(QStringLiteral("Size")).toULongLong();
}

QString UDisksMDRaid::syncAction() const
{
    Q_D(const UDisksMDRaid);
    return d->properties.value(QStringLiteral("SyncAction")).toString();
}

double UDisksMDRaid::syncCompleted() const
{
    Q_D(const UDisksMDRaid);
    return d->properties.value(QStringLiteral("SyncCompleted")).toDouble();
}

qulonglong UDisksMDRaid::syncRate() const
{
    Q_D(const UDisksMDRaid);
    return d->properties.value(QStringLiteral("SyncRate")).toULongLong();
}

qulonglong UDisksMDRaid::syncRemainingTime() const
{
    Q_D(const UDisksMDRaid);
    return d->properties.value(QStringLiteral("SyncRemainingTime")).toULongLong();
}

QString UDisksMDRaid::uUID() const
{
    Q_D(const UDisksMDRaid);
    return d->properties.value(QStringLiteral("UUID")).toString();
}

QDBusPendingReply<> UDisksMDRaid::addDevice(const QDBusObjectPath &device, const QVariantMap &options)
{
    Q_D(UDisksMDRaid);
    return d->interface.AddDevice(device, options);
}

QDBusPendingReply<> UDisksMDRaid::removeDevice(const QDBusObjectPath &device, const QVariantMap &options)
{
    Q_D(UDisksMDRaid);
    return d->interface.RemoveDevice(device, options);
}

QDBusPendingReply<> UDisksMDRaid::requestSyncAction(const QString &syncAction, const QVariantMap &options)
{
    Q_D(UDisksMDRaid);
    return d->interface.RequestSyncAction(syncAction, options);
}

QDBusPendingReply<> UDisksMDRaid::setBitmapLocation(const QByteArray &value, const QVariantMap &options)
{
    Q_D(UDisksMDRaid);
    return d->interface.SetBitmapLocation(value, options);
}

QDBusPendingReply<> UDisksMDRaid::start(const QVariantMap &options)
{
    Q_D(UDisksMDRaid);
    return d->interface.Start(options);
}

QDBusPendingReply<> UDisksMDRaid::stop(const QVariantMap &options)
{
    Q_D(UDisksMDRaid);
    return d->interface.Stop(options);
}

void UDisksMDRaid::propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties)
{
    Q_D(UDisksMDRaid);
    changeProperties(d->properties, properties, invalidProperties);
}

UDisksMDRaidPrivate::UDisksMDRaidPrivate(const QString &path) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus())
{
}
