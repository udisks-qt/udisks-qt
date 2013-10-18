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

#include "udisksfilesystem.h"
#include "udisksfilesystem_p.h"

#include "common.h"

#include <QFile>
#include <QDebug>

UDisksFilesystem::UDisksFilesystem(const QDBusObjectPath &objectPath, const QVariantMap &properties, UDisksObject *parent) :
    UDisksInterface(parent),
    d_ptr(new UDisksFilesystemPrivate(objectPath.path()))
{
    Q_D(UDisksFilesystem);

    d->properties = properties;
}

UDisksFilesystem::~UDisksFilesystem()
{
    delete d_ptr;
}

QStringList UDisksFilesystem::mountPoints() const
{
    Q_D(const UDisksFilesystem);
    QStringList ret;
    QVariant variant = d->properties[QLatin1String("MountPoints")];
    UDByteArrayList mountPoints = qdbus_cast<UDByteArrayList>(variant);
    foreach (const QByteArray &mountPoint, mountPoints) {
        ret << QFile::decodeName(mountPoint);
    }
    return ret;
}

QDBusPendingReply<QString> UDisksFilesystem::mount(const QVariantMap &options)
{
    Q_D(UDisksFilesystem);
    return d->interface.Mount(options);
}

QDBusPendingReply<> UDisksFilesystem::setLabel(const QString &label, const QVariantMap &options)
{
    Q_D(UDisksFilesystem);
    return d->interface.SetLabel(label, options);
}

QDBusPendingReply<> UDisksFilesystem::unmount(const QVariantMap &options)
{
    Q_D(UDisksFilesystem);
    return d->interface.Unmount(options);
}

void UDisksFilesystem::propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties)
{
    Q_D(UDisksFilesystem);
    changeProperties(d->properties, properties, invalidProperties);
}

UDisksFilesystemPrivate::UDisksFilesystemPrivate(const QString &path) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus())
{
}
