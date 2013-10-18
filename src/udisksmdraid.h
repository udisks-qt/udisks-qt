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
#include <QtDBus/QDBusPendingReply>

#include "udisksinterface.h"
#include "dbus-types.h"

class UDisksMDRaidPrivate;
class UDisksMDRaid : public UDisksInterface
{
    Q_OBJECT
public:
    explicit UDisksMDRaid(const QDBusObjectPath &objectPath, const QVariantMap &properties, UDisksObject *parent = 0);
    ~UDisksMDRaid();

    Q_PROPERTY(UDActiveDevice activeDevices READ activeDevices)
    UDActiveDevice activeDevices() const;

    Q_PROPERTY(QByteArray bitmapLocation READ bitmapLocation)
    QByteArray bitmapLocation() const;

    Q_PROPERTY(qulonglong chunkSize READ chunkSize)
    qulonglong chunkSize() const;

    Q_PROPERTY(uint degraded READ degraded)
    uint degraded() const;

    Q_PROPERTY(QString level READ level)
    QString level() const;

    Q_PROPERTY(QString name READ name)
    QString name() const;

    Q_PROPERTY(uint numDevices READ numDevices)
    uint numDevices() const;

    Q_PROPERTY(qulonglong size READ size)
    qulonglong size() const;

    Q_PROPERTY(QString syncAction READ syncAction)
    QString syncAction() const;

    Q_PROPERTY(double syncCompleted READ syncCompleted)
    double syncCompleted() const;

    Q_PROPERTY(qulonglong syncRate READ syncRate)
    qulonglong syncRate() const;

    Q_PROPERTY(qulonglong syncRemainingTime READ syncRemainingTime)
    qulonglong syncRemainingTime() const;

    Q_PROPERTY(QString uUID READ uUID)
    QString uUID() const;

public Q_SLOTS:
    QDBusPendingReply<> addDevice(const QDBusObjectPath &device, const QVariantMap &options = QVariantMap());

    QDBusPendingReply<> removeDevice(const QDBusObjectPath &device, const QVariantMap &options = QVariantMap());

    QDBusPendingReply<> requestSyncAction(const QString &syncAction, const QVariantMap &options = QVariantMap());

    QDBusPendingReply<> setBitmapLocation(const QByteArray &value, const QVariantMap &options = QVariantMap());

    QDBusPendingReply<> start(const QVariantMap &options = QVariantMap());

    QDBusPendingReply<> stop(const QVariantMap &options = QVariantMap());

protected:
    virtual void propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties);
    UDisksMDRaidPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksMDRaid)
};

#endif // UDISKSMDRAID_H
