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

#include "dbus-types.h"

class UDisksDrivePrivate;
class UDisksDrive : public QObject
{
    Q_OBJECT
public:
    explicit UDisksDrive(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties, QObject *parent = 0);

    Q_PROPERTY(bool CanPowerOff READ canPowerOff)
    bool canPowerOff() const;

    Q_PROPERTY(QVariantMap Configuration READ configuration)
    QVariantMap configuration() const;

    Q_PROPERTY(QString ConnectionBus READ connectionBus)
    QString connectionBus() const;

    Q_PROPERTY(bool Ejectable READ ejectable)
    bool ejectable() const;

    Q_PROPERTY(QString Id READ id)
    QString id() const;

    Q_PROPERTY(QString Media READ media)
    QString media() const;

    Q_PROPERTY(bool MediaAvailable READ mediaAvailable)
    bool mediaAvailable() const;

    Q_PROPERTY(bool MediaChangeDetected READ mediaChangeDetected)
    bool mediaChangeDetected() const;

    Q_PROPERTY(QStringList MediaCompatibility READ mediaCompatibility)
    QStringList mediaCompatibility() const;

    Q_PROPERTY(bool MediaRemovable READ mediaRemovable)
    bool mediaRemovable() const;

    Q_PROPERTY(QString Model READ model)
    QString model() const;

    Q_PROPERTY(bool Optical READ optical)
    bool optical() const;

    Q_PROPERTY(bool OpticalBlank READ opticalBlank)
    bool opticalBlank() const;

    Q_PROPERTY(uint OpticalNumAudioTracks READ opticalNumAudioTracks)
    uint opticalNumAudioTracks() const;

    Q_PROPERTY(uint OpticalNumDataTracks READ opticalNumDataTracks)
    uint opticalNumDataTracks() const;

    Q_PROPERTY(uint OpticalNumSessions READ opticalNumSessions)
    uint opticalNumSessions() const;

    Q_PROPERTY(uint OpticalNumTracks READ opticalNumTracks)
    uint opticalNumTracks() const;

    Q_PROPERTY(bool Removable READ removable)
    bool removable() const;

    Q_PROPERTY(QString Revision READ revision)
    QString revision() const;

    Q_PROPERTY(int RotationRate READ rotationRate)
    int rotationRate() const;

    Q_PROPERTY(QString Seat READ seat)
    QString seat() const;

    Q_PROPERTY(QString Serial READ serial)
    QString serial() const;

    Q_PROPERTY(QString SiblingId READ siblingId)
    QString siblingId() const;

    Q_PROPERTY(qulonglong Size READ size)
    qulonglong size() const;

    Q_PROPERTY(QString SortKey READ sortKey)
    QString sortKey() const;

    Q_PROPERTY(qulonglong TimeDetected READ timeDetected)
    qulonglong timeDetected() const;

    Q_PROPERTY(qulonglong TimeMediaDetected READ timeMediaDetected)
    qulonglong timeMediaDetected() const;

    Q_PROPERTY(QString Vendor READ vendor)
    QString vendor() const;

    Q_PROPERTY(QString WWN READ wWN)
    QString wWN() const;

protected:
    UDisksDrivePrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksDrive)
};

#endif // UDISKSDRIVE_H
