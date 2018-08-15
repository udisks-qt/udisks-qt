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

#include "udisksobject.h"
#include "udisksclient.h"
#include "common.h"

#include <QDebug>

UDisksDrive::UDisksDrive(const QDBusObjectPath &objectPath, const QVariantMap &properties, UDisksObject *parent) :
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
    return d->properties.value(QStringLiteral("CanPowerOff")).toBool();
}

QVariantMap UDisksDrive::configuration() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("Configuration")).value<QVariantMap>();
}

QString UDisksDrive::connectionBus() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("ConnectionBus")).toString();
}

bool UDisksDrive::ejectable() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("Ejectable")).toBool();
}

QString UDisksDrive::id() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("Id")).toString();
}

QString UDisksDrive::media() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("Media")).toString();
}

bool UDisksDrive::mediaAvailable() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("MediaAvailable")).toBool();
}

bool UDisksDrive::mediaChangeDetected() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("MediaChangeDetected")).toBool();
}

QStringList UDisksDrive::mediaCompatibility() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("MediaCompatibility")).toStringList();
}

bool UDisksDrive::mediaRemovable() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("MediaRemovable")).toBool();
}

QString UDisksDrive::model() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("Model")).toString();
}

bool UDisksDrive::optical() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("Optical")).toBool();
}

bool UDisksDrive::opticalBlank() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("OpticalBlank")).toBool();
}

uint UDisksDrive::opticalNumAudioTracks() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("OpticalNumAudioTracks")).toUInt();
}

uint UDisksDrive::opticalNumDataTracks() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("OpticalNumDataTracks")).toUInt();
}

uint UDisksDrive::opticalNumSessions() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("OpticalNumSessions")).toUInt();
}

uint UDisksDrive::opticalNumTracks() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("OpticalNumTracks")).toUInt();
}

bool UDisksDrive::removable() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("Removable")).toBool();
}

QString UDisksDrive::revision() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("Revision")).toString();
}

int UDisksDrive::rotationRate() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("RotationRate")).toInt();
}

QString UDisksDrive::seat() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("Seat")).toString();
}

QString UDisksDrive::serial() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("Serial")).toString();
}

QString UDisksDrive::siblingId() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("SiblingId")).toString();
}

qulonglong UDisksDrive::size() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("Size")).toULongLong();
}

QString UDisksDrive::sortKey() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("SortKey")).toString();
}

qulonglong UDisksDrive::timeDetected() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("TimeDetected")).toULongLong();
}

qulonglong UDisksDrive::timeMediaDetected() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("TimeMediaDetected")).toULongLong();
}

QString UDisksDrive::vendor() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("Vendor")).toString();
}

QString UDisksDrive::wWN() const
{
    Q_D(const UDisksDrive);
    return d->properties.value(QStringLiteral("WWN")).toString();
}

UDisksBlock *UDisksDrive::getBlock()
{
    Q_D(const UDisksDrive);
    const UDisksObject::List blocks = UDisksDrivePrivate::topLevelBlocks(object()->client(), d->interface.path());
    for (const UDisksObject::Ptr &object : blocks) {
        if (object->block()) {
            return object->block();
        }
    }
    return nullptr;
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

UDisksObject::List UDisksDrivePrivate::topLevelBlocks(UDisksClient *client, const QString &driveObjectPath)
{
    UDisksObject::List ret;
    const auto objects = client->getObjects(UDisksObject::BlockDevice);
    for (const UDisksObject::Ptr &object : objects) {
        UDisksBlock *block = object->block();
        if (!block) {
            continue;
        }

        if (block->drive().path() == driveObjectPath && object->partition() == nullptr) {
            ret.append(object);
        }
    }
    return ret;
}
