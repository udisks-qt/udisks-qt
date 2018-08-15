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

#include "udisksobject_p.h"

#include "common.h"

#include "udisksmanager.h"
#include "udisksblock.h"
#include "udisksdrive.h"
#include "udisksdriveata.h"
#include "udisksmdraid.h"
#include "udiskspartition.h"
#include "udiskspartitiontable.h"
#include "udisksfilesystem.h"
#include "udisksswapspace.h"
#include "udisksencrypted.h"
#include "udisksloop.h"
#include "udisksjob.h"

#include <QtDBus/QDBusConnection>

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(UDISKSQT_OBJECT, "udisksqt.object")

UDisksObject::UDisksObject(const QDBusObjectPath &objectPath, const UDVariantMapMap &interfacesAndProperties, UDisksClient *client) :
    d_ptr(new UDisksObjectPrivate(objectPath, client, this))
{
    Q_D(UDisksObject);

    QDBusConnection::systemBus().connect(UD2_SERVICE,
                                         objectPath.path(),
                                         DBUS_PROPERTIES,
                                         QLatin1String("PropertiesChanged"),
                                         this,
                                         SLOT(_q_propertiesChanged(QString,QVariantMap,QStringList)));

    // Initializa the kind of the object
    const QString &path = objectPath.path();
    if (path.startsWith(QLatin1String(UD2_PATH_BLOCK_DEVICES))) {
        d->kind = BlockDevice;
    } else if (path.startsWith(QLatin1String(UD2_PATH_DRIVES))) {
        d->kind = Drive;
    } else if (path.startsWith(QLatin1String(UD2_PATH_MDRAID))) {
        d->kind = MDRaid;
    } else if (path.startsWith(QLatin1String(UD2_PATH_JOBS))) {
        d->kind = Job;
    } else if (path.startsWith(QLatin1String(UD2_PATH_MANAGER))) {
        d->kind = Manager;
    } else {
        qCWarning(UDISKSQT_OBJECT) << "Unknown udisk object please report a bug:" << path;
        d->kind = Unknown;
    }

    // Create the object interfaces
    UDVariantMapMap::ConstIterator it = interfacesAndProperties.constBegin();
    while (it != interfacesAndProperties.constEnd()) {
        d->_q_addInterface(it.key(), it.value(), false);

        ++it;
    }
}

UDisksObject::~UDisksObject()
{
    delete d_ptr;
}

UDisksObject::Kind UDisksObject::kind() const
{
    Q_D(const UDisksObject);
    return d->kind;
}

QDBusObjectPath UDisksObject::path() const
{
    Q_D(const UDisksObject);
    return d->object;
}

UDisksObject::Interfaces UDisksObject::interfaces() const
{
    Q_D(const UDisksObject);
    return d->interfaces;
}

UDisksClient *UDisksObject::client() const
{
    Q_D(const UDisksObject);
    return d->client;
}

UDisksManager *UDisksObject::manager() const
{
    Q_D(const UDisksObject);
    return d->manager;
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

UDisksFilesystem *UDisksObject::filesystem() const
{
    Q_D(const UDisksObject);
    return d->filesystem;
}

UDisksSwapspace *UDisksObject::swapspace() const
{
    Q_D(const UDisksObject);
    return d->swapspace;
}

UDisksEncrypted *UDisksObject::encrypted() const
{
    Q_D(const UDisksObject);
    return d->encrypted;
}

UDisksLoop *UDisksObject::loop() const
{
    Q_D(const UDisksObject);
    return d->loop;
}

bool UDisksObject::addInterfaces(const UDVariantMapMap &interfacesAndProperties)
{
    Q_D(UDisksObject);
    bool ret = false;

    // Create the object interfaces
    UDVariantMapMap::ConstIterator it = interfacesAndProperties.constBegin();
    while (it != interfacesAndProperties.constEnd()) {
        if (d->_q_addInterface(it.key(), it.value(), true)) {
            ret = true;
        }

        ++it;
    }
    return ret;
}

bool UDisksObject::removeInterfaces(const QStringList &interfaces)
{
    Q_D(UDisksObject);

    bool ret = false;
    for (const QString &interface : interfaces) {
        if (d->_q_removeInterface(interface)) {
            ret = true;
        }
    }

    return ret;
}

UDisksObject::Interface UDisksObject::interfaceEnumFromString(const QString &interface) const
{
    if (interface == QLatin1String(UD2_INTERFACE_BLOCK)) {
        return UDisksObject::InterfaceBlock;
    } else if (interface == QLatin1String(UD2_INTERFACE_DRIVE)) {
        return UDisksObject::InterfaceDrive;
    } else if (interface == QLatin1String(UD2_INTERFACE_DRIVE_ATA)) {
        return UDisksObject::InterfaceDriveAta;
    } else if (interface == QLatin1String(UD2_INTERFACE_MDRAID)) {
        return UDisksObject::InterfaceMDRaid;
    } else if (interface == QLatin1String(UD2_INTERFACE_MANAGER)) {
        return UDisksObject::InterfaceManager;
    } else if (interface == QLatin1String(UD2_INTERFACE_PARTITION)) {
        return UDisksObject::InterfacePartition;
    } else if (interface == QLatin1String(UD2_INTERFACE_PARTITION_TABLE)) {
        return UDisksObject::InterfacePartitionTable;
    } else if (interface == QLatin1String(UD2_INTERFACE_FILESYSTEM)) {
        return UDisksObject::InterfaceFilesystem;
    } else if (interface == QLatin1String(UD2_INTERFACE_SWAPSPACE)) {
        return UDisksObject::InterfaceSwapspace;
    } else if (interface == QLatin1String(UD2_INTERFACE_ENCRYPTION)) {
        return UDisksObject::InterfaceEncrypted;
    } else if (interface == QLatin1String(UD2_INTERFACE_LOOP)) {
        return UDisksObject::InterfaceLoop;
    } else if (interface == QLatin1String(UD2_INTERFACE_JOB)) {
        return UDisksObject::InterfaceJob;
    } else {
        qCWarning(UDISKSQT_OBJECT) << "Unknown interface to enum, please report a bug:" << interface;
        return UDisksObject::InterfaceNone;
    }
}

UDisksObjectPrivate::UDisksObjectPrivate(const QDBusObjectPath &path, UDisksClient *uDClient, UDisksObject *parent)
    : q_ptr(parent)
    , client(uDClient)
    , object(path)
{
}

bool UDisksObjectPrivate::_q_addInterface(const QString &interface, const QVariantMap &properties, bool emitSignal)
{
    Q_Q(UDisksObject);

    bool ret = false;
    UDisksObject::Interface interfaceEnum = q->interfaceEnumFromString(interface);
    switch (interfaceEnum) {
    case UDisksObject::InterfaceBlock:
        if (block == nullptr) {
            block = new UDisksBlock(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceDrive:
        if (drive == nullptr) {
            drive = new UDisksDrive(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceDriveAta:
        if (driveAta == nullptr) {
            driveAta = new UDisksDriveAta(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceMDRaid:
        if (mDRaid == nullptr) {
            mDRaid = new UDisksMDRaid(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceManager:
        if (manager == nullptr) {
            manager = new UDisksManager(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfacePartition:
        if (partition == nullptr) {
            partition = new UDisksPartition(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfacePartitionTable:
        if (partitionTable == nullptr) {
            partitionTable = new UDisksPartitionTable(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceFilesystem:
        if (filesystem == nullptr) {
            filesystem = new UDisksFilesystem(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceSwapspace:
        if (swapspace == nullptr) {
            swapspace = new UDisksSwapspace(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceEncrypted:
        if (encrypted == nullptr) {
            encrypted = new UDisksEncrypted(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceLoop:
        if (loop == nullptr) {
            loop = new UDisksLoop(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceJob:
        if (job == nullptr) {
            job = new UDisksJob(object, properties, q);
            ret = true;
        }
        break;
    default:
        qCWarning(UDISKSQT_OBJECT) << "Unknown interface to add, please report a bug:" << interface;
        break;
    }

    if (ret) {
        interfaces |= interfaceEnum;
        if (emitSignal) {
            q->interfaceAdded(interfaceEnum);
        }
    }

    return ret;
}

bool UDisksObjectPrivate::_q_removeInterface(const QString &interface)
{
    Q_Q(UDisksObject);

    bool ret = false;
    UDisksObject::Interface interfaceEnum = q->interfaceEnumFromString(interface);
    switch (interfaceEnum) {
    case UDisksObject::InterfaceBlock:
        if (block) {
            block->deleteLater();
            block = nullptr;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceDrive:
        if (drive) {
            drive->deleteLater();
            drive = nullptr;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceDriveAta:
        if (driveAta) {
            driveAta->deleteLater();
            driveAta = nullptr;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceMDRaid:
        if (mDRaid) {
            mDRaid->deleteLater();
            mDRaid = nullptr;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceManager:
        if (manager) {
            manager->deleteLater();
            manager = nullptr;
            ret = true;
        }
        break;
    case UDisksObject::InterfacePartition:
        if (partition) {
            partition->deleteLater();
            partition = nullptr;
            ret = true;
        }
        break;
    case UDisksObject::InterfacePartitionTable:
        if (partitionTable) {
            partitionTable->deleteLater();
            partitionTable = nullptr;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceFilesystem:
        if (filesystem) {
            filesystem->deleteLater();
            filesystem = nullptr;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceSwapspace:
        if (swapspace) {
            swapspace->deleteLater();
            swapspace = nullptr;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceEncrypted:
        if (encrypted) {
            encrypted->deleteLater();
            encrypted = nullptr;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceLoop:
        if (loop) {
            loop->deleteLater();
            loop = nullptr;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceJob:
        if (job) {
            job->deleteLater();
            job = nullptr;
            ret = true;
        }
        break;
    default:
        qCWarning(UDISKSQT_OBJECT) << "Unknown interface to remove, please report a bug:" << interface;
        break;
    }

    if (ret) {
        interfaces ^= interfaceEnum;
        q->interfaceRemoved(interfaceEnum);
    }

    return ret;
}

void UDisksObjectPrivate::_q_propertiesChanged(const QString &interface, const QVariantMap &properties, const QStringList &invalidatedProperties)
{
    Q_Q(UDisksObject);

    qCDebug(UDISKSQT_OBJECT) << "Properties changed" << interface;

    UDisksInterface *interfacePointer = nullptr;
    UDisksObject::Interface interfaceEnum = q->interfaceEnumFromString(interface);
    switch (interfaceEnum) {
    case UDisksObject::InterfaceBlock:
        if (block) {
            interfacePointer = block;
        }
        break;
    case UDisksObject::InterfaceDrive:
        if (drive) {
            interfacePointer = drive;
        }
        break;
    case UDisksObject::InterfaceDriveAta:
        if (driveAta) {
            interfacePointer = driveAta;
        }
        break;
    case UDisksObject::InterfaceMDRaid:
        if (mDRaid) {
            interfacePointer = mDRaid;
        }
        break;
    case UDisksObject::InterfaceManager:
        if (manager) {
            interfacePointer = manager;
        }
        break;
    case UDisksObject::InterfacePartition:
        if (partition) {
            interfacePointer = partition;
        }
        break;
    case UDisksObject::InterfacePartitionTable:
        if (partitionTable) {
            interfacePointer = partitionTable;
        }
        break;
    case UDisksObject::InterfaceFilesystem:
        if (filesystem) {
            interfacePointer = filesystem;
        }
        break;
    case UDisksObject::InterfaceSwapspace:
        if (swapspace) {
            interfacePointer = swapspace;
        }
        break;
    case UDisksObject::InterfaceEncrypted:
        if (encrypted) {
            interfacePointer = encrypted;
        }
        break;
    case UDisksObject::InterfaceLoop:
        if (loop) {
            interfacePointer = loop;
        }
        break;
    case UDisksObject::InterfaceJob:
        if (job) {
            interfacePointer = job;
        }
        break;
    default:
        qCWarning(UDISKSQT_OBJECT) << "Unknown interface to change, please report a bug:" << interface;
        break;
    }

    if (interfacePointer) {
        interfacePointer->propertiesChanged(properties, invalidatedProperties);
        q->propertiesChanged(interfaceEnum);
    }
}

#include "moc_udisksobject.cpp"
