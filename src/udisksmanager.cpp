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

UDisksManager::UDisksManager(const QDBusObjectPath &objectPath, const QVariantMap &properties, UDisksObject *parent) :
    UDisksInterface(parent),
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
    return d->properties.value(QStringLiteral("Version")).toString();
}

QStringList UDisksManager::supportedFilesystems() const
{
    Q_D(const UDisksManager);
    return d->properties.value(QStringLiteral("SupportedFilesystems")).toStringList();
}

QDBusPendingReply<UDisksTypeAvailable> UDisksManager::canCheck(const QString &type)
{
    Q_D(UDisksManager);
    return d->interface.CanCheck(type);
}

QDBusPendingReply<UDisksTypeAvailable> UDisksManager::canFormat(const QString &type)
{
    Q_D(UDisksManager);
    return d->interface.CanFormat(type);
}

QDBusPendingReply<UDisksTypeAvailable> UDisksManager::canRepair(const QString &type)
{
    Q_D(UDisksManager);
    return d->interface.CanRepair(type);
}

QDBusPendingReply<UDisksTypeAvailableFlags> UDisksManager::canResize(const QString &type)
{
    Q_D(UDisksManager);
    return d->interface.CanResize(type);
}

QDBusPendingReply<> UDisksManager::enableModules(bool enable)
{
    Q_D(UDisksManager);
    return d->interface.EnableModules(enable);
}

QDBusPendingReply<QList<QDBusObjectPath> > UDisksManager::getBlockDevices(const QVariantMap &options)
{
    Q_D(UDisksManager);
    return d->interface.GetBlockDevices(options);
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

QDBusPendingReply<QList<QDBusObjectPath> > UDisksManager::resolveDevice(const QVariantMap &devspec, const QVariantMap &options)
{
    Q_D(UDisksManager);
    return d->interface.ResolveDevice(devspec, options);
}

void UDisksManager::propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties)
{
    Q_D(UDisksManager);
    changeProperties(d->properties, properties, invalidProperties);
}

UDisksManagerPrivate::UDisksManagerPrivate(const QDBusObjectPath &object) :
    interface(QLatin1String(UD2_SERVICE),
              object.path(),
              QDBusConnection::systemBus())
{
}
