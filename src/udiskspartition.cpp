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

#include "udiskspartition.h"
#include "udiskspartition_p.h"

#include "common.h"

#include <QDebug>

UDisksPartition::UDisksPartition(const QDBusObjectPath &objectPath, const QVariantMap &properties, QObject *parent) :
    UDisksInterface(parent),
    d_ptr(new UDisksPartitionPrivate(objectPath.path()))
{
    Q_D(UDisksPartition);

    d->properties = properties;
}

UDisksPartition::~UDisksPartition()
{
    delete d_ptr;
}

qulonglong UDisksPartition::flags() const
{
    Q_D(const UDisksPartition);
    return d->properties[QLatin1String("Flags")].toULongLong();
}

bool UDisksPartition::isContained() const
{
    Q_D(const UDisksPartition);
    return d->properties[QLatin1String("IsContained")].toBool();
}

bool UDisksPartition::isContainer() const
{
    Q_D(const UDisksPartition);
    return d->properties[QLatin1String("IsContainer")].toBool();
}

QString UDisksPartition::name() const
{
    Q_D(const UDisksPartition);
    return d->properties[QLatin1String("Name")].toString();
}

uint UDisksPartition::number() const
{
    Q_D(const UDisksPartition);
    return d->properties[QLatin1String("Number")].toUInt();
}

qulonglong UDisksPartition::offset() const
{
    Q_D(const UDisksPartition);
    return d->properties[QLatin1String("Offset")].toULongLong();
}

qulonglong UDisksPartition::size() const
{
    Q_D(const UDisksPartition);
    return d->properties[QLatin1String("Size")].toULongLong();
}

QDBusObjectPath UDisksPartition::table() const
{
    Q_D(const UDisksPartition);
    return d->properties[QLatin1String("Table")].value<QDBusObjectPath>();
}

QString UDisksPartition::type() const
{
    Q_D(const UDisksPartition);
    return d->properties[QLatin1String("Type")].toString();
}

QString UDisksPartition::uUID() const
{
    Q_D(const UDisksPartition);
    return d->properties[QLatin1String("UUID")].toString();
}

QDBusPendingReply<> UDisksPartition::deletePartition(const QVariantMap &options)
{
    Q_D(UDisksPartition);
    return d->interface.Delete(options);
}

QDBusPendingReply<> UDisksPartition::setFlags(qulonglong flags, const QVariantMap &options)
{
    Q_D(UDisksPartition);
    return d->interface.SetFlags(flags, options);
}

QDBusPendingReply<> UDisksPartition::setName(const QString &name, const QVariantMap &options)
{
    Q_D(UDisksPartition);
    return d->interface.SetName(name, options);
}

QDBusPendingReply<> UDisksPartition::setType(const QString &type, const QVariantMap &options)
{
    Q_D(UDisksPartition);
    return d->interface.SetType(type, options);
}

void UDisksPartition::propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties)
{
    Q_D(UDisksPartition);
    changeProperties(d->properties, properties, invalidProperties);
}

UDisksPartitionPrivate::UDisksPartitionPrivate(const QString &path) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus())
{
}
