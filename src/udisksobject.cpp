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
#include <QDebug>

UDisksObject::UDisksObject(const QDBusObjectPath &objectPath, const UDVariantMapMap &interfacesAndProperties) :
    d_ptr(new UDisksObjectPrivate(objectPath, this))
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
        qWarning() << "Block Devices";
        d->kind = BlockDevice;
    } else if (path.startsWith(QLatin1String(UD2_PATH_DRIVES))) {
        qWarning() << "Drives";
        d->kind = Drive;
    } else if (path.startsWith(QLatin1String(UD2_PATH_MDRAID))) {
        qWarning() << "MDRaid";
        d->kind = MDRaid;
    } else if (path.startsWith(QLatin1String(UD2_PATH_JOBS))) {
        qWarning() << "Jobs";
        d->kind = Job;
    } else if (path.startsWith(QLatin1String(UD2_PATH_MANAGER))) {
        qWarning() << "Manager";
        d->kind = Manager;
    } else {
        qWarning() << Q_FUNC_INFO << "Unknown udisk object please report a bug:" << path;
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
    foreach (const QString &interface, interfaces) {
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
        qWarning() << Q_FUNC_INFO << "Unknown interface, please report a bug:" << interface;
        return UDisksObject::InterfaceNone;
    }
}

UDisksObjectPrivate::UDisksObjectPrivate(const QDBusObjectPath &path, UDisksObject *parent) :
    q_ptr(parent),
    object(path),
    interfaces(UDisksObject::InterfaceNone),
    kind(UDisksObject::Unknown),
    manager(0),
    drive(0),
    driveAta(0),
    mDRaid(0),
    block(0),
    partition(0),
    partitionTable(0),
    filesystem(0),
    swapspace(0),
    encrypted(0),
    loop(0)
{
}

bool UDisksObjectPrivate::_q_addInterface(const QString &interface, const QVariantMap &properties, bool emitSignal)
{
    Q_Q(UDisksObject);

    bool ret = false;
    UDisksObject::Interface interfaceEnum = q->interfaceEnumFromString(interface);
    switch (interfaceEnum) {
    case UDisksObject::InterfaceBlock:
        if (block == 0) {
            block = new UDisksBlock(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceDrive:
        if (drive == 0) {
            drive = new UDisksDrive(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceDriveAta:
        if (driveAta == 0) {
            driveAta = new UDisksDriveAta(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceMDRaid:
        if (mDRaid == 0) {
            mDRaid = new UDisksMDRaid(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceManager:
        if (manager == 0) {
            manager = new UDisksManager(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfacePartition:
        if (partition == 0) {
            partition = new UDisksPartition(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfacePartitionTable:
        if (partitionTable == 0) {
            partitionTable = new UDisksPartitionTable(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceFilesystem:
        if (filesystem == 0) {
            filesystem = new UDisksFilesystem(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceSwapspace:
        if (swapspace == 0) {
            swapspace = new UDisksSwapspace(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceEncrypted:
        if (encrypted == 0) {
            encrypted = new UDisksEncrypted(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceLoop:
        if (loop == 0) {
            loop = new UDisksLoop(object, properties, q);
            ret = true;
        }
        break;
    case UDisksObject::InterfaceJob:
        if (job == 0) {
            job = new UDisksJob(object, properties, q);
            ret = true;
        }
        break;
    default:
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
            block->removeInterface();
            block = 0;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceDrive:
        if (drive) {
            drive->removeInterface();
            drive = 0;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceDriveAta:
        if (driveAta) {
            driveAta->removeInterface();
            driveAta = 0;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceMDRaid:
        if (mDRaid) {
            mDRaid->removeInterface();
            mDRaid = 0;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceManager:
        if (manager) {
            manager->removeInterface();
            manager = 0;
            ret = true;
        }
        break;
    case UDisksObject::InterfacePartition:
        if (partition) {
            partition->removeInterface();
            partition = 0;
            ret = true;
        }
        break;
    case UDisksObject::InterfacePartitionTable:
        if (partitionTable) {
            partitionTable->removeInterface();
            partitionTable = 0;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceFilesystem:
        if (filesystem) {
            filesystem->removeInterface();
            filesystem = 0;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceSwapspace:
        if (swapspace) {
            swapspace->removeInterface();
            swapspace = 0;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceEncrypted:
        if (encrypted) {
            encrypted->removeInterface();
            encrypted = 0;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceLoop:
        if (loop) {
            loop->removeInterface();
            loop = 0;
            ret = true;
        }
        break;
    case UDisksObject::InterfaceJob:
        if (job) {
            job->removeInterface();
            job = 0;
            ret = true;
        }
        break;
    default:
        qWarning() << Q_FUNC_INFO << "Unknown interface, please report a bug:" << interface;
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

    qDebug() << Q_FUNC_INFO << interface;
    qDebug() << properties;
    qDebug() << invalidatedProperties;
    UDisksInterface *interfacePointer = 0;
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
        qWarning() << Q_FUNC_INFO << "Unknown interface, please report a bug:" << interface;
        break;
    }

    if (interfacePointer) {
        interfacePointer->propertiesChanged(properties, invalidatedProperties);
        q->propertiesChanged(interfaceEnum);
    }
}

#include "moc_udisksobject.cpp"
