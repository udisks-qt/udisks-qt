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

class UDisksClient;
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
    Q_ENUM(Kind)

    enum Interface {
        InterfaceNone           = 1 << 0,
        InterfaceManager        = 1 << 1,
        InterfaceDrive          = 1 << 2,
        InterfaceDriveAta       = 1 << 3,
        InterfaceMDRaid         = 1 << 4,
        InterfaceJob            = 1 << 5,
        InterfaceBlock          = 1 << 6,
        InterfacePartition      = 1 << 7,
        InterfacePartitionTable = 1 << 8,
        InterfaceFilesystem     = 1 << 9,
        InterfaceSwapspace      = 1 << 10,
        InterfaceEncrypted      = 1 << 11,
        InterfaceLoop           = 1 << 12
    };
    Q_DECLARE_FLAGS(Interfaces, Interface)
    Q_FLAG(Interfaces)

    ~UDisksObject();

    Q_PROPERTY(Kind kind READ kind)
    Kind kind() const;

    Q_PROPERTY(QDBusObjectPath path READ path)
    QDBusObjectPath path() const;

    Q_PROPERTY(Interfaces interfaces READ interfaces)
    Interfaces interfaces() const;

    UDisksClient *client() const;
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

Q_SIGNALS:
    void interfaceAdded(Interface interface);
    void interfaceRemoved(Interface interface);
    void propertiesChanged(Interface interface);

protected:
    UDisksObject(const QDBusObjectPath &objectPath, const UDisksVariantMapMap &interfacesAndProperties, UDisksClient *client);
    bool addInterfaces(const UDisksVariantMapMap &interfacesAndProperties);
    bool removeInterfaces(const QStringList &interfaces);
    Interface interfaceEnumFromString(const QString &interface) const;

    UDisksObjectPrivate *d_ptr;

private:
    friend class UDisksClientPrivate;
    friend class UDisksClient;
    Q_DECLARE_PRIVATE(UDisksObject)
    Q_PRIVATE_SLOT(d_func(), void _q_propertiesChanged(QString,QVariantMap,QStringList))
};

#endif // UDISKSOBJECT_H
