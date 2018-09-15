/*
 * Copyright (C) 2013-2018 Daniel Nicoletti <dantti12@gmail.com>
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

#ifndef GENERIC_TYPES_H
#define GENERIC_TYPES_H

#include <QtCore/QVariantMap>
#include <QtDBus/QDBusArgument>
#include <QtCore/QVariantMap>


typedef QMap<QString,QVariantMap> UDisksVariantMapMap;
Q_DECLARE_METATYPE(UDisksVariantMapMap)

typedef QMap<QDBusObjectPath, UDisksVariantMapMap> UDisksManagedObjects;
Q_DECLARE_METATYPE(UDisksManagedObjects)

typedef struct
{
    QString name;
    QVariantMap values;
} UDisksItem;
QDBusArgument &operator<<(QDBusArgument &argument, const UDisksItem &item);
const QDBusArgument &operator>>(const QDBusArgument &argument, UDisksItem &item);
Q_DECLARE_METATYPE(UDisksItem)

typedef QList<UDisksItem> UDisksItemList;
Q_DECLARE_METATYPE(UDisksItemList)

typedef struct
{
    quint8 id;
    QString name;
    quint16 flags;
    int value;
    int worst;
    int threshold;
    qint64 pretty;
    int pretty_unit;
    QVariantMap expansion;
} UDisksAttributes;
QDBusArgument &operator<<(QDBusArgument &argument, const UDisksAttributes &attributes);
const QDBusArgument &operator>>(const QDBusArgument &argument, UDisksAttributes &attributes);
Q_DECLARE_METATYPE(UDisksAttributes)

typedef struct
{
    QDBusObjectPath block;
    int slot;
    QStringList state;
    quint64 num_read_errors;
    QVariantMap expansion;
} UDisksActiveDevice;
QDBusArgument &operator<<(QDBusArgument &argument, const UDisksActiveDevice &activeDevice);
const QDBusArgument &operator>>(const QDBusArgument &argument, UDisksActiveDevice &activeDevice);
Q_DECLARE_METATYPE(UDisksActiveDevice)

typedef struct
{
    bool available;
    QString value;
} UDisksTypeAvailable;
QDBusArgument &operator<<(QDBusArgument &argument, const UDisksTypeAvailable &item);
const QDBusArgument &operator>>(const QDBusArgument &argument, UDisksTypeAvailable &item);
Q_DECLARE_METATYPE(UDisksTypeAvailable)

typedef struct
{
    bool available;
    quint64 flags;
    QString value;
} UDisksTypeAvailableFlags;
QDBusArgument &operator<<(QDBusArgument &argument, const UDisksTypeAvailableFlags &item);
const QDBusArgument &operator>>(const QDBusArgument &argument, UDisksTypeAvailableFlags &item);
Q_DECLARE_METATYPE(UDisksTypeAvailableFlags)

#endif // GENERIC_TYPES_H
