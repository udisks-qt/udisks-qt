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

#include "udiskspartitiontable.h"
#include "udiskspartitiontable_p.h"

#include "common.h"

#include <QDebug>

UDisksPartitionTable::UDisksPartitionTable(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties, QObject *parent) :
    QObject(parent),
    d_ptr(new UDisksPartitionTablePrivate(objectPath.path()))
{
    Q_D(UDisksPartitionTable);

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

QString UDisksPartitionTable::type() const
{
    Q_D(const UDisksPartitionTable);
    return d->type;
}

UDisksPartitionTablePrivate::UDisksPartitionTablePrivate(const QString &path) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus())
{
}

void UDisksPartitionTablePrivate::init(const QVariantMap &properties)
{
    QVariantMap::ConstIterator it = properties.constBegin();
    while (it != properties.constEnd()) {
        const QString &property = it.key();
        const QVariant &value = it.value();
        qDebug() << Q_FUNC_INFO << property << value;

        if (property == QLatin1String("Type")) {
            type = value.toString();
        } else {
            qWarning() << Q_FUNC_INFO << "Unknown property, please report a bug:" << property << value;
        }

        ++it;
    }
}



