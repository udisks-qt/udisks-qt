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


UDisksManager::UDisksManager(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties, QObject *parent) :
    QObject(parent),
    d_ptr(new UDisksManagerPrivate(this))
{

}

UDisksManager::~UDisksManager()
{
}

QString UDisksManager::version() const
{
    Q_D(const UDisksManager);
    return d->version;
}

//Block::Ptr UDisksManager::loopSetup(int fileDescriptor)
//{

//}

//MDRaid::Ptr UDisksManager::MDRaidCreate(const QStringList &blocks, const QString &level, const QString &name, qulonglong chunk, const QVariantMap &options)
//{

//}

void UDisksManager::serviceOwnerChanged(const QString &service, const QString &oldOwner, const QString &newOwner)
{
    Q_UNUSED(service)
    Q_UNUSED(oldOwner)
    Q_D(UDisksManager);

    if (!newOwner.isEmpty()) {
        d->init();
    }
}

void UDisksManager::callFinishedSlot(QDBusPendingCallWatcher *call)
{
    Q_D(UDisksManager);
    qWarning() << Q_FUNC_INFO;
    QDBusPendingReply<UDManagedObjects> reply = *call;
    if (reply.isError()) {
//        showError();
        qWarning() << Q_FUNC_INFO << reply.error().message();
    } else {
        UDManagedObjects objects = reply.value();
        UDManagedObjects::ConstIterator it = objects.constBegin();
        while (it != objects.constEnd()) {
            proccessObject(it.key(), it.value());
            ++it;
        }
    }
    call->deleteLater();
}

void UDisksManager::proccessObject(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties)
{
    Q_D(UDisksManager);

    const QString &path = objectPath.path();
    if (path.startsWith(QLatin1String(UD2_PATH_BLOCK_DEVICES))) {
        qWarning() << "Block Devices";
        UDisksBlock *block = new UDisksBlock(objectPath, interfacesAndProperties);
    } else if (path.startsWith(QLatin1String(UD2_PATH_DRIVES))) {
        qWarning() << "Drives";
        UDisksDrive *drive = new UDisksDrive(objectPath, interfacesAndProperties);
    } else if (path.startsWith(QLatin1String(UD2_PATH_MDRAID))) {
        qWarning() << "MDRaid";
    } else if (path.startsWith(QLatin1String(UD2_PATH_JOBS))) {
        qWarning() << "Jobs";
    } else if (path.startsWith(QLatin1String(UD2_PATH_MANAGER))) {
        qWarning() << "Manager";
        UDVariantMapMap::ConstIterator it = interfacesAndProperties.constBegin();
        while (it != interfacesAndProperties.constEnd()) {
            const QString &interface = it.key();
            const QVariantMap &values = it.value();

            if (interface == QLatin1String(UD2_INTERFACE_MANAGER)) {
                QVariantMap::ConstIterator it2 = values.constBegin();
                while (it2 != values.constEnd()) {
                    const QString &property = it2.key();
                    const QVariant &value = it2.value();

                    if (property == QLatin1String("Version")) {
                        d->version = value.toString();
                        emit versionChanged();
                    } else {
                        qWarning() << Q_FUNC_INFO << "Unknown property, please report a bug:" << property << value;
                    }

                    ++it2;
                }
            } else {
                qWarning() << Q_FUNC_INFO << "Unknown interface, please report a bug:" << interface;
            }

            ++it;
        }
    } else {
        qWarning() << Q_FUNC_INFO << "Unknown udisk object please report a bug:" << path;
    }
}


UDisksManagerPrivate::UDisksManagerPrivate(UDisksManager *parent) :
    interface(QLatin1String(UD2_SERVICE),
              QLatin1String(UD2_PATH_MANAGER),
              QDBusConnection::systemBus())
{

}
