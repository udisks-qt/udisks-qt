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

#include <QDebug>

UDisksObject::UDisksObject(const QDBusObjectPath &objectPath, const UDVariantMapMap &interfacesAndProperties) :
    d_ptr(new UDisksObjectPrivate(objectPath, this))
{
    Q_D(UDisksObject);

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

QStringList UDisksObject::interfaces() const
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

UDisksObjectPrivate::UDisksObjectPrivate(const QDBusObjectPath &path, UDisksObject *parent) :
    q_ptr(parent),
    object(path),
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
    if (interface == QLatin1String(UD2_INTERFACE_BLOCK)) {
        if (block == 0) {
            block = new UDisksBlock(object, properties, q);
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_DRIVE)) {
        if (drive == 0) {
            drive = new UDisksDrive(object, properties, q);
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_DRIVE_ATA)) {
        if (driveAta == 0) {
            driveAta = new UDisksDriveAta(object, properties, q);
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_MDRAID)) {
        if (mDRaid == 0) {
            mDRaid = new UDisksMDRaid(object, properties, q);
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_MANAGER)) {
        if (manager == 0) {
            manager = new UDisksManager(object, properties, q);
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_PARTITION)) {
        if (partition == 0) {
            partition = new UDisksPartition(object, properties, q);
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_PARTITION_TABLE)) {
        if (partitionTable == 0) {
            partitionTable = new UDisksPartitionTable(object, properties, q);
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_FILESYSTEM)) {
        if (filesystem == 0) {
            filesystem = new UDisksFilesystem(object, properties, q);
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_SWAPSPACE)) {
        if (swapspace == 0) {
            swapspace = new UDisksSwapspace(object, properties, q);
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_ENCRYPTION)) {
        if (encrypted == 0) {
            encrypted = new UDisksEncrypted(object, properties, q);
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_LOOP)) {
        if (loop == 0) {
            loop = new UDisksLoop(object, properties, q);
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_JOB)) {
        if (job == 0) {
            job = new UDisksJob(object, properties, q);
            ret = true;
        }
    } else {
        qWarning() << Q_FUNC_INFO << "Unknown interface, please report a bug:" << interface;
    }

    if (ret) {
        interfaces << interface;
        if (emitSignal) {
            q->interfaceAdded(interface);
        }
    }

    return ret;
}

bool UDisksObjectPrivate::_q_removeInterface(const QString &interface)
{
    Q_Q(UDisksObject);

    bool ret = false;
    if (interface == QLatin1String(UD2_INTERFACE_BLOCK)) {
        if (block) {
            block->deleteLater();
            block = 0;
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_DRIVE)) {
        if (drive) {
            drive->deleteLater();
            drive = 0;
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_DRIVE_ATA)) {
        if (driveAta) {
            driveAta->deleteLater();
            driveAta = 0;
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_MDRAID)) {
        if (mDRaid) {
            mDRaid->deleteLater();
            mDRaid = 0;
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_MANAGER)) {
        if (manager) {
            manager->deleteLater();
            manager = 0;
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_PARTITION)) {
        if (partition) {
            partition->deleteLater();
            partition = 0;
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_PARTITION_TABLE)) {
        if (partitionTable) {
            partitionTable->deleteLater();
            partitionTable = 0;
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_FILESYSTEM)) {
        if (filesystem) {
            filesystem->deleteLater();
            filesystem = 0;
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_SWAPSPACE)) {
        if (swapspace) {
            swapspace->deleteLater();
            swapspace = 0;
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_ENCRYPTION)) {
        if (encrypted) {
            encrypted->deleteLater();
            encrypted = 0;
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_LOOP)) {
        if (loop) {
            loop->deleteLater();
            loop = 0;
            ret = true;
        }
    } else if (interface == QLatin1String(UD2_INTERFACE_JOB)) {
        if (job) {
            job->deleteLater();
            job = 0;
            ret = true;
        }
    } else {
        qWarning() << Q_FUNC_INFO << "Unknown interface, please report a bug:" << interface;
    }

    if (ret) {
        interfaces.removeOne(interface);
        q->interfaceRemoved(interface);
    }

    return ret;
}
