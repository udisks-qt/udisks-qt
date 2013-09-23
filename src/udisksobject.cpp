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

#include "udisksobject.h"
#include "udisksobject_p.h"

#include "common.h"

#include <QDebug>

UDisksObject::UDisksObject(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties, QObject *parent) :
    QObject(parent),
    d_ptr(new UDisksObjectPrivate(objectPath.path()))
{
    Q_D(UDisksObject);

    UDVariantMapMap::ConstIterator it = interfacesAndProperties.constBegin();
    while (it != interfacesAndProperties.constEnd()) {
        const QString &interface = it.key();
        if (interface == QLatin1String(UD2_INTERFACE_DRIVE)) {
            d->init(it.value());
        } else {
            qWarning() << Q_FUNC_INFO << "Unknown interface, please report a bug:" << interface;
        }

        ++it;
    }
}

UDisksDrive *UDisksObject::drive() const
{
    Q_D(const UDisksObject);
    return d->drive;
}

UDisksDriveAta *UDisksObject::driveAta() const
{
    Q_D(const UDisksObject);
    return d->driveAta;
}

UDisksMDRaid *UDisksObject::mDRaid() const
{
    Q_D(const UDisksObject);
    return d->mDRaid;
}

UDisksJob *UDisksObject::job() const
{
    Q_D(const UDisksObject);
    return d->job;
}

UDisksBlock *UDisksObject::block() const
{
    Q_D(const UDisksObject);
    return d->block;
}

UDisksPartition *UDisksObject::partition() const
{
    Q_D(const UDisksObject);
    return d->partition;
}

UDisksPartitionTable *UDisksObject::partitionTable() const
{
    Q_D(const UDisksObject);
    return d->partitionTable;
}

UDisksObjectPrivate::UDisksObjectPrivate(const QString &path) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus()),
    drive(0),
    driveAta(0),
    block(0),
    partition(0),
    partitionTable(0)
{
}

void UDisksObjectPrivate::init(const QVariantMap &properties)
{
    QVariantMap::ConstIterator it = properties.constBegin();
    while (it != properties.constEnd()) {
        const QString &property = it.key();
        const QVariant &value = it.value();
        qDebug() << Q_FUNC_INFO << property << value;

        ++it;
    }
}
