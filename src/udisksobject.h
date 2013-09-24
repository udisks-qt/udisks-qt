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

#ifndef UDISKSOBJECT_H
#define UDISKSOBJECT_H

#include <QtCore/QObject>
#include <QtDBus/QDBusObjectPath>

#include "dbus-types.h"

class UDisksManager;
class UDisksDrive;
class UDisksDriveAta;
class UDisksMDRaid;
class UDisksJob;
class UDisksBlock;
class UDisksPartition;
class UDisksPartitionTable;
class UDisksFilesystem;
class UDisksSwapspace;
class UDisksEncrypted;
class UDisksLoop;

class UDisksObjectPrivate;
class UDisksObject : public QObject
{
    Q_OBJECT
public:
    typedef QSharedPointer<UDisksObject> Ptr;
    typedef QList<Ptr> List;

    enum Kind {
        Unknown,
        Any,
        Manager,
        BlockDevice,
        Drive,
        MDRaid,
        Job
    };

    ~UDisksObject();

    Q_PROPERTY(Kind kind READ kind)
    Kind kind() const;

    Q_PROPERTY(QDBusObjectPath path READ path)
    QDBusObjectPath path() const;

    UDisksManager *manager() const;
    UDisksDrive *drive() const;
    UDisksDriveAta *driveAta() const;
    UDisksMDRaid *mDRaid() const;
    UDisksJob *job() const;
    UDisksBlock *block() const;
    UDisksPartition *partition() const;
    UDisksPartitionTable *partitionTable() const;
    UDisksFilesystem *filesystem() const;
    UDisksSwapspace *swapspace() const;
    UDisksEncrypted *encrypted() const;
    UDisksLoop *loop() const;

protected:
    UDisksObject(const QDBusObjectPath &objectPath, const UDVariantMapMap &interfacesAndProperties);
    void addInterfaces(const UDVariantMapMap &interfacesAndProperties);
    void removeInterfaces(const QStringList &interfaces);

    UDisksObjectPrivate *d_ptr;

private:
    friend class UDisksClientPrivate;
    Q_DECLARE_PRIVATE(UDisksObject)
};

#endif // UDISKSOBJECT_H
