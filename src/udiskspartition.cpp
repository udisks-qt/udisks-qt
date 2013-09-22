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

UDisksPartition::UDisksPartition(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties, QObject *parent) :
    QObject(parent),
    d_ptr(new UDisksPartitionPrivate(objectPath.path()))
{
    Q_D(UDisksPartition);

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

qulonglong UDisksPartition::flags() const
{
    Q_D(const UDisksPartition);
    return d->flags;
}

bool UDisksPartition::isContained() const
{
    Q_D(const UDisksPartition);
    return d->isContained;
}

bool UDisksPartition::isContainer() const
{
    Q_D(const UDisksPartition);
    return d->isContainer;
}

QString UDisksPartition::name() const
{
    Q_D(const UDisksPartition);
    return d->name;
}

uint UDisksPartition::number() const
{
    Q_D(const UDisksPartition);
    return d->number;
}

qulonglong UDisksPartition::offset() const
{
    Q_D(const UDisksPartition);
    return d->offset;
}

qulonglong UDisksPartition::size() const
{
    Q_D(const UDisksPartition);
    return d->size;
}

QDBusObjectPath UDisksPartition::table() const
{
    Q_D(const UDisksPartition);
    return d->table;
}

QString UDisksPartition::type() const
{
    Q_D(const UDisksPartition);
    return d->type;
}

QString UDisksPartition::uUID() const
{
    Q_D(const UDisksPartition);
    return d->uUID;
}

UDisksPartitionPrivate::UDisksPartitionPrivate(const QString &path) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus())
{
}

void UDisksPartitionPrivate::init(const QVariantMap &properties)
{
    QVariantMap::ConstIterator it = properties.constBegin();
    while (it != properties.constEnd()) {
        const QString &property = it.key();
        const QVariant &value = it.value();
        qDebug() << Q_FUNC_INFO << property << value;

        if (property == QLatin1String("Flags")) {
            flags = value.toULongLong();
        } else if (property == QLatin1String("IsContained")) {
            isContained = value.toBool();
        } else if (property == QLatin1String("IsContainer")) {
            isContainer = value.toBool();
        } else if (property == QLatin1String("Name")) {
            name = value.toString();
        } else if (property == QLatin1String("Number")) {
            number = value.toUInt();
        } else if (property == QLatin1String("Offset")) {
            offset = value.toULongLong();
        } else if (property == QLatin1String("Size")) {
            size = value.toULongLong();
        } else if (property == QLatin1String("Table")) {
            table = value.value<QDBusObjectPath>();
        } else if (property == QLatin1String("Type")) {
            type = value.toString();
        } else if (property == QLatin1String("UUID")) {
            uUID = value.toString();
        } else {
            qWarning() << Q_FUNC_INFO << "Unknown property, please report a bug:" << property << value;
        }

        ++it;
    }
}



