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

UDisksMDRaid::UDisksMDRaid(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties, QObject *parent) :
    QObject(parent),
    d_ptr(new UDisksMDRaidPrivate(objectPath.path()))
{
    Q_D(UDisksMDRaid);

    UDVariantMapMap::ConstIterator it = interfacesAndProperties.constBegin();
    while (it != interfacesAndProperties.constEnd()) {
        const QString &interface = it.key();
        if (interface == QLatin1String(UD2_INTERFACE_BLOCK)) {
            d->properties = it.value();
        } else {
            qWarning() << Q_FUNC_INFO << "Unknown interface, please report a bug:" << interface;
        }

        ++it;
    }
}

UDActiveDevice UDisksMDRaid::activeDevices() const
{
    Q_D(const UDisksMDRaid);
    return d->properties[QLatin1String("ActiveDevices")].value<UDActiveDevice>();
}

QByteArray UDisksMDRaid::bitmapLocation() const
{
    Q_D(const UDisksMDRaid);
    return d->properties[QLatin1String("BitmapLocation")].toByteArray();
}

qulonglong UDisksMDRaid::chunkSize() const
{
    Q_D(const UDisksMDRaid);
    return d->properties[QLatin1String("ChunkSize")].toULongLong();
}

uint UDisksMDRaid::degraded() const
{
    Q_D(const UDisksMDRaid);
    return d->properties[QLatin1String("Degraded")].toUInt();
}

QString UDisksMDRaid::level() const
{
    Q_D(const UDisksMDRaid);
    return d->properties[QLatin1String("Level")].toString();
}

QString UDisksMDRaid::name() const
{
    Q_D(const UDisksMDRaid);
    return d->properties[QLatin1String("Name")].toString();
}

uint UDisksMDRaid::numDevices() const
{
    Q_D(const UDisksMDRaid);
    return d->properties[QLatin1String("NumDevices")].toUInt();
}

qulonglong UDisksMDRaid::size() const
{
    Q_D(const UDisksMDRaid);
    return d->properties[QLatin1String("Size")].toULongLong();
}

QString UDisksMDRaid::syncAction() const
{
    Q_D(const UDisksMDRaid);
    return d->properties[QLatin1String("SyncAction")].toString();
}

double UDisksMDRaid::syncCompleted() const
{
    Q_D(const UDisksMDRaid);
    return d->properties[QLatin1String("SyncCompleted")].toDouble();
}

qulonglong UDisksMDRaid::syncRate() const
{
    Q_D(const UDisksMDRaid);
    return d->properties[QLatin1String("SyncRate")].toULongLong();
}

qulonglong UDisksMDRaid::syncRemainingTime() const
{
    Q_D(const UDisksMDRaid);
    return d->properties[QLatin1String("SyncRemainingTime")].toULongLong();
}

QString UDisksMDRaid::uUID() const
{
    Q_D(const UDisksMDRaid);
    return d->properties[QLatin1String("UUID")].toString();
}

UDisksMDRaidPrivate::UDisksMDRaidPrivate(const QString &path) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus())
{
}

void UDisksMDRaidPrivate::init(const QVariantMap &properties)
{
}



