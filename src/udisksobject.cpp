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
    d_ptr(new UDisksObjectPrivate(objectPath))
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

    addInterfaces(interfacesAndProperties);
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

void UDisksObject::addInterfaces(const UDVariantMapMap &interfacesAndProperties)
{
    Q_D(UDisksObject);

    // Create the object interfaces
    UDVariantMapMap::ConstIterator it = interfacesAndProperties.constBegin();
    while (it != interfacesAndProperties.constEnd()) {
        const QString &interface = it.key();
        if (interface == QLatin1String(UD2_INTERFACE_BLOCK)) {
            d->block = new UDisksBlock(d->object, it.value(), this);
        } else if (interface == QLatin1String(UD2_INTERFACE_DRIVE)) {
            d->drive = new UDisksDrive(d->object, it.value(), this);
        } else if (interface == QLatin1String(UD2_INTERFACE_DRIVE_ATA)) {
            d->driveAta = new UDisksDriveAta(d->object, it.value(), this);
        } else if (interface == QLatin1String(UD2_INTERFACE_MDRAID)) {
            d->mDRaid = new UDisksMDRaid(d->object, it.value(), this);
        } else if (interface == QLatin1String(UD2_INTERFACE_MANAGER)) {
            d->manager = new UDisksManager(d->object, it.value(), this);
        } else if (interface == QLatin1String(UD2_INTERFACE_PARTITION)) {
            d->partition = new UDisksPartition(d->object, it.value(), this);
        } else if (interface == QLatin1String(UD2_INTERFACE_PARTITION_TABLE)) {
            d->partitionTable = new UDisksPartitionTable(d->object, it.value(), this);
        } else if (interface == QLatin1String(UD2_INTERFACE_FILESYSTEM)) {
            d->filesystem = new UDisksFilesystem(d->object, it.value(), this);
        } else if (interface == QLatin1String(UD2_INTERFACE_SWAPSPACE)) {
            d->swapspace = new UDisksSwapspace(d->object, it.value(), this);
        } else if (interface == QLatin1String(UD2_INTERFACE_ENCRYPTION)) {
            d->encrypted = new UDisksEncrypted(d->object, it.value(), this);
        } else if (interface == QLatin1String(UD2_INTERFACE_LOOP)) {
            d->loop = new UDisksLoop(d->object, it.value(), this);
        } else if (interface == QLatin1String(UD2_INTERFACE_JOB)) {
            d->job = new UDisksJob(d->object, it.value(), this);
        } else {
            qWarning() << Q_FUNC_INFO << "Unknown interface, please report a bug:" << interface;
        }

        ++it;
    }
}

void UDisksObject::removeInterfaces(const QStringList &interfaces)
{
    Q_D(UDisksObject);

    foreach (const QString &interface, interfaces) {
        if (interface == QLatin1String(UD2_INTERFACE_BLOCK)) {
            d->block->deleteLater();
            d->block = 0;
        } else if (interface == QLatin1String(UD2_INTERFACE_DRIVE)) {
            d->drive->deleteLater();
            d->drive = 0;
        } else if (interface == QLatin1String(UD2_INTERFACE_DRIVE_ATA)) {
            d->driveAta->deleteLater();
            d->driveAta = 0;
        } else if (interface == QLatin1String(UD2_INTERFACE_MDRAID)) {
            d->mDRaid->deleteLater();
            d->mDRaid = 0;
        } else if (interface == QLatin1String(UD2_INTERFACE_MANAGER)) {
            d->manager->deleteLater();
            d->manager = 0;
        } else if (interface == QLatin1String(UD2_INTERFACE_PARTITION)) {
            d->partition->deleteLater();
            d->partition = 0;
        } else if (interface == QLatin1String(UD2_INTERFACE_PARTITION_TABLE)) {
            d->partitionTable->deleteLater();
            d->partitionTable = 0;
        } else if (interface == QLatin1String(UD2_INTERFACE_FILESYSTEM)) {
            d->filesystem->deleteLater();
            d->filesystem = 0;
        } else if (interface == QLatin1String(UD2_INTERFACE_SWAPSPACE)) {
            d->swapspace->deleteLater();
            d->swapspace = 0;
        } else if (interface == QLatin1String(UD2_INTERFACE_ENCRYPTION)) {
            d->encrypted->deleteLater();
            d->encrypted = 0;
        } else if (interface == QLatin1String(UD2_INTERFACE_LOOP)) {
            d->loop->deleteLater();
            d->loop = 0;
        } else if (interface == QLatin1String(UD2_INTERFACE_JOB)) {
            d->job->deleteLater();
            d->job = 0;
        } else {
            qWarning() << Q_FUNC_INFO << "Unknown interface, please report a bug:" << interface;
        }
    }
}

UDisksObjectPrivate::UDisksObjectPrivate(const QDBusObjectPath &path) :
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
