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

#include "udisksdrive.h"
#include "udisksdrive_p.h"

#include "common.h"

#include <QDebug>

UDisksDrive::UDisksDrive(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties, QObject *parent) :
    QObject(parent),
    d_ptr(new UDisksDrivePrivate(objectPath.path()))
{
    Q_D(UDisksDrive);

    UDVariantMapMap::ConstIterator it = interfacesAndProperties.constBegin();
    while (it != interfacesAndProperties.constEnd()) {
        const QString &interface = it.key();
        if (interface == QLatin1String(UD2_INTERFACE_DRIVE)) {
            d->init(it.value());
        } else {
            qWarning() << Q_FUNC_INFO << "Unknown interface, please report a bug:" << interface;
        }

        ++it;
    }
}

bool UDisksDrive::canPowerOff() const
{
    Q_D(const UDisksDrive);
    return d->canPowerOff;
}

QVariantMap UDisksDrive::configuration() const
{
    Q_D(const UDisksDrive);
    return d->configuration;
}

QString UDisksDrive::connectionBus() const
{
    Q_D(const UDisksDrive);
    return d->connectionBus;
}

bool UDisksDrive::ejectable() const
{
    Q_D(const UDisksDrive);
    return d->ejectable;
}

QString UDisksDrive::id() const
{
    Q_D(const UDisksDrive);
    return d->id;
}

QString UDisksDrive::media() const
{
    Q_D(const UDisksDrive);
    return d->media;
}

bool UDisksDrive::mediaAvailable() const
{
    Q_D(const UDisksDrive);
    return d->mediaAvailable;
}

bool UDisksDrive::mediaChangeDetected() const
{
    Q_D(const UDisksDrive);
    return d->mediaChangeDetected;
}

QStringList UDisksDrive::mediaCompatibility() const
{
    Q_D(const UDisksDrive);
    return d->mediaCompatibility;
}

bool UDisksDrive::mediaRemovable() const
{
    Q_D(const UDisksDrive);
    return d->mediaRemovable;
}

QString UDisksDrive::model() const
{
    Q_D(const UDisksDrive);
    return d->model;
}

bool UDisksDrive::optical() const
{
    Q_D(const UDisksDrive);
    return d->optical;
}

bool UDisksDrive::opticalBlank() const
{
    Q_D(const UDisksDrive);
    return d->opticalBlank;
}

uint UDisksDrive::opticalNumAudioTracks() const
{
    Q_D(const UDisksDrive);
    return d->opticalNumAudioTracks;
}

uint UDisksDrive::opticalNumDataTracks() const
{
    Q_D(const UDisksDrive);
    return d->opticalNumDataTracks;
}

uint UDisksDrive::opticalNumSessions() const
{
    Q_D(const UDisksDrive);
    return d->opticalNumSessions;
}

uint UDisksDrive::opticalNumTracks() const
{
    Q_D(const UDisksDrive);
    return d->opticalNumTracks;
}

bool UDisksDrive::removable() const
{
    Q_D(const UDisksDrive);
    return d->removable;
}

QString UDisksDrive::revision() const
{
    Q_D(const UDisksDrive);
    return d->revision;
}

int UDisksDrive::rotationRate() const
{
    Q_D(const UDisksDrive);
    return d->rotationRate;
}

QString UDisksDrive::seat() const
{
    Q_D(const UDisksDrive);
    return d->seat;
}

QString UDisksDrive::serial() const
{
    Q_D(const UDisksDrive);
    return d->serial;
}

QString UDisksDrive::siblingId() const
{
    Q_D(const UDisksDrive);
    return d->siblingId;
}

qulonglong UDisksDrive::size() const
{
    Q_D(const UDisksDrive);
    return d->size;
}

QString UDisksDrive::sortKey() const
{
    Q_D(const UDisksDrive);
    return d->sortKey;
}

qulonglong UDisksDrive::timeDetected() const
{
    Q_D(const UDisksDrive);
    return d->timeDetected;
}

qulonglong UDisksDrive::timeMediaDetected() const
{
    Q_D(const UDisksDrive);
    return d->timeMediaDetected;
}

QString UDisksDrive::vendor() const
{
    Q_D(const UDisksDrive);
    return d->vendor;
}

QString UDisksDrive::wWN() const
{
    Q_D(const UDisksDrive);
    return d->wWN;
}

UDisksDrivePrivate::UDisksDrivePrivate(const QString &path) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus())
{
}

void UDisksDrivePrivate::init(const QVariantMap &properties)
{
    QVariantMap::ConstIterator it = properties.constBegin();
    while (it != properties.constEnd()) {
        const QString &property = it.key();
        const QVariant &value = it.value();
        qDebug() << Q_FUNC_INFO << property << value;

        if (property == QLatin1String("CanPowerOff")) {
            canPowerOff = value.toBool();
        } else if (property == QLatin1String("Configuration")) {
            configuration = value.value<QVariantMap>();
        } else if (property == QLatin1String("ConnectionBus")) {
            connectionBus = value.toString();
        } else if (property == QLatin1String("Ejectable")) {
            ejectable = value.toBool();
        } else if (property == QLatin1String("Id")) {
            id = value.toString();
        } else if (property == QLatin1String("Media")) {
            media = value.toString();
        } else if (property == QLatin1String("MediaAvailable")) {
            mediaAvailable = value.toBool();
        } else if (property == QLatin1String("MediaChangeDetected")) {
            mediaChangeDetected = value.toBool();
        } else if (property == QLatin1String("MediaCompatibility")) {
            mediaCompatibility = value.toStringList();
        } else if (property == QLatin1String("MediaRemovable")) {
            mediaRemovable = value.toBool();
        } else if (property == QLatin1String("Model")) {
            model = value.toString();
        } else if (property == QLatin1String("Optical")) {
            optical = value.toBool();
        } else if (property == QLatin1String("OpticalBlank")) {
            opticalBlank = value.toBool();
        } else if (property == QLatin1String("OpticalNumAudioTracks")) {
            opticalNumAudioTracks = value.toUInt();
        } else if (property == QLatin1String("OpticalNumDataTracks")) {
            opticalNumDataTracks = value.toUInt();
        } else if (property == QLatin1String("OpticalNumSessions")) {
            opticalNumSessions = value.toUInt();
        } else if (property == QLatin1String("OpticalNumTracks")) {
            opticalNumTracks = value.toUInt();
        } else if (property == QLatin1String("Removable")) {
            removable = value.toBool();
        } else if (property == QLatin1String("Revision")) {
            revision = value.toString();
        } else if (property == QLatin1String("RotationRate")) {
            rotationRate = value.toInt();
        } else if (property == QLatin1String("Seat")) {
            seat = value.toString();
        } else if (property == QLatin1String("Serial")) {
            serial = value.toString();
        } else if (property == QLatin1String("SiblingId")) {
            siblingId = value.toString();
        } else if (property == QLatin1String("Size")) {
            size = value.toULongLong();
        } else if (property == QLatin1String("SortKey")) {
            sortKey = value.toString();
        } else if (property == QLatin1String("TimeDetected")) {
            timeDetected = value.toULongLong();
        } else if (property == QLatin1String("TimeMediaDetected")) {
            timeMediaDetected = value.toULongLong();
        } else if (property == QLatin1String("Vendor")) {
            vendor = value.toString();
        } else if (property == QLatin1String("WWN")) {
            wWN = value.toString();
        } else {
            qWarning() << Q_FUNC_INFO << "Unknown property, please report a bug:" << property << value;
        }

        ++it;
    }
}
