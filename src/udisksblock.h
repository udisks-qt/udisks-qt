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

#ifndef UDISKSBLOCK_H
#define UDISKSBLOCK_H

#include <QObject>

#include "dbus-types.h"

class UDisksBlockPrivate;
class UDisksBlock : public QObject
{
    Q_OBJECT
public:
    explicit UDisksBlock(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties, QObject *parent = 0);

    Q_PROPERTY(QList<UDItem> Configuration READ configuration)
    QList<UDItem> configuration() const;

    Q_PROPERTY(QDBusObjectPath CryptoBackingDevice READ cryptoBackingDevice)
    QDBusObjectPath cryptoBackingDevice() const;

    Q_PROPERTY(QByteArray Device READ device)
    QByteArray device() const;

    Q_PROPERTY(qulonglong DeviceNumber READ deviceNumber)
    qulonglong deviceNumber() const;

    Q_PROPERTY(QDBusObjectPath Drive READ drive)
    QDBusObjectPath drive() const;

    Q_PROPERTY(bool HintAuto READ hintAuto)
    bool hintAuto() const;

    Q_PROPERTY(QString HintIconName READ hintIconName)
    QString hintIconName() const;

    Q_PROPERTY(bool HintIgnore READ hintIgnore)
    bool hintIgnore() const;

    Q_PROPERTY(QString HintName READ hintName)
    QString hintName() const;

    Q_PROPERTY(bool HintPartitionable READ hintPartitionable)
    bool hintPartitionable() const;

    Q_PROPERTY(QString HintSymbolicIconName READ hintSymbolicIconName)
    QString hintSymbolicIconName() const;

    Q_PROPERTY(bool HintSystem READ hintSystem)
    bool hintSystem() const;

    Q_PROPERTY(QString Id READ id)
    QString id() const;

    Q_PROPERTY(QString IdLabel READ idLabel)
    QString idLabel() const;

    Q_PROPERTY(QString IdType READ idType)
    QString idType() const;

    Q_PROPERTY(QString IdUUID READ idUUID)
    QString idUUID() const;

    Q_PROPERTY(QString IdUsage READ idUsage)
    QString idUsage() const;

    Q_PROPERTY(QString IdVersion READ idVersion)
    QString idVersion() const;

    Q_PROPERTY(QDBusObjectPath MDRaid READ mDRaid)
    QDBusObjectPath mDRaid() const;

    Q_PROPERTY(QDBusObjectPath MDRaidMember READ mDRaidMember)
    QDBusObjectPath mDRaidMember() const;

    Q_PROPERTY(QByteArray PreferredDevice READ preferredDevice)
    QByteArray preferredDevice() const;

    Q_PROPERTY(bool ReadOnly READ readOnly)
    bool readOnly() const;

    Q_PROPERTY(qulonglong Size READ size)
    qulonglong size() const;

    Q_PROPERTY(QList<QByteArray> Symlinks READ symlinks)
    QList<QByteArray> symlinks() const;

protected:
    UDisksBlockPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksBlock)
};

#endif // UDISKSBLOCK_H
