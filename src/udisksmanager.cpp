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


#include "udisksmanager.h"
#include "udisksmanager_p.h"

#include "udisksdrive.h"
#include "udisksblock.h"
#include "UDisks.h"
#include "DBusObjectManager.h"

#include "common.h"

#include <QDebug>


UDisksManager::UDisksManager(const QDBusObjectPath &objectPath, const QVariantMap &properties, QObject *parent) :
    QObject(parent),
    d_ptr(new UDisksManagerPrivate(objectPath))
{
    Q_D(UDisksManager);

    d->properties = properties;
}

UDisksManager::~UDisksManager()
{
    delete d_ptr;
}

QString UDisksManager::version() const
{
    Q_D(const UDisksManager);
    return d->properties[QLatin1String("Version")].toString();
}

QDBusPendingReply<QDBusObjectPath> UDisksManager::loopSetup(const QDBusUnixFileDescriptor &fd, const QVariantMap &options)
{
    Q_D(UDisksManager);
    return d->interface.LoopSetup(fd, options);
}

QDBusPendingReply<QDBusObjectPath> UDisksManager::mDRaidCreate(const QList<QDBusObjectPath> &blocks, const QString &level, const QString &name, qulonglong chunk, const QVariantMap &options)
{
    Q_D(UDisksManager);
    return d->interface.MDRaidCreate(blocks, level, name, chunk, options);
}

UDisksManagerPrivate::UDisksManagerPrivate(const QDBusObjectPath &object) :
    interface(QLatin1String(UD2_SERVICE),
              object.path(),
              QDBusConnection::systemBus())
{
}
