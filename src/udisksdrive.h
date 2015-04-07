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

#ifndef UDISKSDRIVE_H
#define UDISKSDRIVE_H

#include <QObject>
#include <QtDBus/QDBusPendingReply>

#include "udisksblock.h"
#include "udisksinterface.h"
#include "dbus-types.h"

class UDisksObject;
class UDisksDrivePrivate;
class UDisksDrive : public UDisksInterface
{
    Q_OBJECT
public:
    explicit UDisksDrive(const QDBusObjectPath &objectPath, const QVariantMap &properties, UDisksObject *parent = 0);
    ~UDisksDrive();

    Q_PROPERTY(bool canPowerOff READ canPowerOff)
    bool canPowerOff() const;

    Q_PROPERTY(QVariantMap configuration READ configuration)
    QVariantMap configuration() const;

    Q_PROPERTY(QString connectionBus READ connectionBus)
    QString connectionBus() const;

    Q_PROPERTY(bool ejectable READ ejectable)
    bool ejectable() const;

    Q_PROPERTY(QString driveId READ id)
    QString id() const;

    Q_PROPERTY(QString media READ media)
    QString media() const;

    Q_PROPERTY(bool mediaAvailable READ mediaAvailable)
    bool mediaAvailable() const;

    Q_PROPERTY(bool mediaChangeDetected READ mediaChangeDetected)
    bool mediaChangeDetected() const;

    Q_PROPERTY(QStringList mediaCompatibility READ mediaCompatibility)
    QStringList mediaCompatibility() const;

    Q_PROPERTY(bool mediaRemovable READ mediaRemovable)
    bool mediaRemovable() const;

    Q_PROPERTY(QString model READ model)
    QString model() const;

    Q_PROPERTY(bool optical READ optical)
    bool optical() const;

    Q_PROPERTY(bool opticalBlank READ opticalBlank)
    bool opticalBlank() const;

    Q_PROPERTY(uint opticalNumAudioTracks READ opticalNumAudioTracks)
    uint opticalNumAudioTracks() const;

    Q_PROPERTY(uint opticalNumDataTracks READ opticalNumDataTracks)
    uint opticalNumDataTracks() const;

    Q_PROPERTY(uint opticalNumSessions READ opticalNumSessions)
    uint opticalNumSessions() const;

    Q_PROPERTY(uint opticalNumTracks READ opticalNumTracks)
    uint opticalNumTracks() const;

    Q_PROPERTY(bool removable READ removable)
    bool removable() const;

    Q_PROPERTY(QString revision READ revision)
    QString revision() const;

    Q_PROPERTY(int rotationRate READ rotationRate)
    int rotationRate() const;

    Q_PROPERTY(QString seat READ seat)
    QString seat() const;

    Q_PROPERTY(QString serial READ serial)
    QString serial() const;

    Q_PROPERTY(QString siblingId READ siblingId)
    QString siblingId() const;

    Q_PROPERTY(qulonglong size READ size)
    qulonglong size() const;

    Q_PROPERTY(QString sortKey READ sortKey)
    QString sortKey() const;

    Q_PROPERTY(qulonglong timeDetected READ timeDetected)
    qulonglong timeDetected() const;

    Q_PROPERTY(qulonglong timeMediaDetected READ timeMediaDetected)
    qulonglong timeMediaDetected() const;

    Q_PROPERTY(QString vendor READ vendor)
    QString vendor() const;

    Q_PROPERTY(QString wWN READ wWN)
    QString wWN() const;

    /**
     * @brief Get the main block device associated with
     * this drive, do not delete this pointer.
     * @return the block device associated with this drive
     */
    UDisksBlock* getBlock();

public Q_SLOTS:
    QDBusPendingReply<> eject(const QVariantMap &options = QVariantMap());

    QDBusPendingReply<> powerOff(const QVariantMap &options = QVariantMap());

    QDBusPendingReply<> setConfiguration(const QVariantMap &value, const QVariantMap &options = QVariantMap());

protected:
    virtual void propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties);
    UDisksDrivePrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksDrive)
};

#endif // UDISKSDRIVE_H
