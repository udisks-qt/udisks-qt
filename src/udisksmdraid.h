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

#ifndef UDISKSMDRAID_H
#define UDISKSMDRAID_H

#include <QObject>

#include "dbus-types.h"

class UDisksMDRaidPrivate;
class UDisksMDRaid : public QObject
{
    Q_OBJECT
public:
    explicit UDisksMDRaid(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties, QObject *parent = 0);

    Q_PROPERTY(UDActiveDevice ActiveDevices READ activeDevices)
    UDActiveDevice activeDevices() const;

    Q_PROPERTY(QByteArray BitmapLocation READ bitmapLocation)
    QByteArray bitmapLocation() const;

    Q_PROPERTY(qulonglong ChunkSize READ chunkSize)
    qulonglong chunkSize() const;

    Q_PROPERTY(uint Degraded READ degraded)
    uint degraded() const;

    Q_PROPERTY(QString Level READ level)
    QString level() const;

    Q_PROPERTY(QString Name READ name)
    QString name() const;

    Q_PROPERTY(uint NumDevices READ numDevices)
    uint numDevices() const;

    Q_PROPERTY(qulonglong Size READ size)
    qulonglong size() const;

    Q_PROPERTY(QString SyncAction READ syncAction)
    QString syncAction() const;

    Q_PROPERTY(double SyncCompleted READ syncCompleted)
    double syncCompleted() const;

    Q_PROPERTY(qulonglong SyncRate READ syncRate)
    qulonglong syncRate() const;

    Q_PROPERTY(qulonglong SyncRemainingTime READ syncRemainingTime)
    qulonglong syncRemainingTime() const;

    Q_PROPERTY(QString UUID READ uUID)
    QString uUID() const;

protected:
    UDisksMDRaidPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksMDRaid)
};

#endif // UDISKSMDRAID_H
