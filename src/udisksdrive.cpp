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

UDisksDrive::UDisksDrive(const QDBusObjectPath &objectPath, const QVariantMap &properties, QObject *parent) :
    UDisksInterface(parent),
    d_ptr(new UDisksDrivePrivate(objectPath.path(), properties))
{
}

UDisksDrive::~UDisksDrive()
{
    delete d_ptr;
}

bool UDisksDrive::canPowerOff() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("CanPowerOff")].toBool();
}

QVariantMap UDisksDrive::configuration() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("Configuration")].value<QVariantMap>();
}

QString UDisksDrive::connectionBus() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("ConnectionBus")].toString();
}

bool UDisksDrive::ejectable() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("Ejectable")].toBool();
}

QString UDisksDrive::id() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("Id")].toString();
}

QString UDisksDrive::media() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("Media")].toString();
}

bool UDisksDrive::mediaAvailable() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("MediaAvailable")].toBool();
}

bool UDisksDrive::mediaChangeDetected() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("MediaChangeDetected")].toBool();
}

QStringList UDisksDrive::mediaCompatibility() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("MediaCompatibility")].toStringList();
}

bool UDisksDrive::mediaRemovable() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("MediaRemovable")].toBool();
}

QString UDisksDrive::model() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("Model")].toString();
}

bool UDisksDrive::optical() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("Optical")].toBool();
}

bool UDisksDrive::opticalBlank() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("OpticalBlank")].toBool();
}

uint UDisksDrive::opticalNumAudioTracks() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("OpticalNumAudioTracks")].toUInt();
}

uint UDisksDrive::opticalNumDataTracks() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("OpticalNumDataTracks")].toUInt();
}

uint UDisksDrive::opticalNumSessions() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("OpticalNumSessions")].toUInt();
}

uint UDisksDrive::opticalNumTracks() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("OpticalNumTracks")].toUInt();
}

bool UDisksDrive::removable() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("Removable")].toBool();
}

QString UDisksDrive::revision() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("Revision")].toString();
}

int UDisksDrive::rotationRate() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("RotationRate")].toInt();
}

QString UDisksDrive::seat() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("Seat")].toString();
}

QString UDisksDrive::serial() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("Serial")].toString();
}

QString UDisksDrive::siblingId() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("SiblingId")].toString();
}

qulonglong UDisksDrive::size() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("Size")].toULongLong();
}

QString UDisksDrive::sortKey() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("SortKey")].toString();
}

qulonglong UDisksDrive::timeDetected() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("TimeDetected")].toULongLong();
}

qulonglong UDisksDrive::timeMediaDetected() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("TimeMediaDetected")].toULongLong();
}

QString UDisksDrive::vendor() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("Vendor")].toString();
}

QString UDisksDrive::wWN() const
{
    Q_D(const UDisksDrive);
    return d->properties[QLatin1String("WWN")].toString();
}

QDBusPendingReply<> UDisksDrive::eject(const QVariantMap &options)
{
    Q_D(UDisksDrive);
    return d->interface.Eject(options);
}

QDBusPendingReply<> UDisksDrive::powerOff(const QVariantMap &options)
{
    Q_D(UDisksDrive);
    return d->interface.PowerOff(options);
}

QDBusPendingReply<> UDisksDrive::setConfiguration(const QVariantMap &value, const QVariantMap &options)
{
    Q_D(UDisksDrive);
    return d->interface.SetConfiguration(value, options);
}

void UDisksDrive::propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties)
{
    Q_D(UDisksDrive);
    changeProperties(d->properties, properties, invalidProperties);
}

UDisksDrivePrivate::UDisksDrivePrivate(const QString &path, const QVariantMap &propertiesMap) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus()),
    properties(propertiesMap)
{
}
