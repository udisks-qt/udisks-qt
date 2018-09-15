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

#include "udisksdriveata.h"
#include "udisksdriveata_p.h"

#include "common.h"

#include <QDebug>

UDisksDriveAta::UDisksDriveAta(const QDBusObjectPath &objectPath, const QVariantMap &properties, UDisksObject *parent) :
    UDisksInterface(parent),
    d_ptr(new UDisksDriveAtaPrivate(objectPath.path()))
{
    Q_D(UDisksDriveAta);

    d->properties = properties;
}

UDisksDriveAta::~UDisksDriveAta()
{
    delete d_ptr;
}

bool UDisksDriveAta::aamEnabled() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("AamEnabled")).toBool();
}

bool UDisksDriveAta::aamSupported() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("AamSupported")).toBool();
}

int UDisksDriveAta::aamVendorRecommendedValue() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("AamVendorRecommendedValue")).toInt();
}

bool UDisksDriveAta::apmEnabled() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("ApmEnabled")).toBool();
}

bool UDisksDriveAta::apmSupported() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("ApmSupported")).toBool();
}

bool UDisksDriveAta::pmEnabled() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("PmEnabled")).toBool();
}

bool UDisksDriveAta::pmSupported() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("PmSupported")).toBool();
}

int UDisksDriveAta::securityEnhancedEraseUnitMinutes() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("SecurityEnhancedEraseUnitMinutes")).toInt();
}

int UDisksDriveAta::securityEraseUnitMinutes() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("SecurityEraseUnitMinutes")).toInt();
}

bool UDisksDriveAta::securityFrozen() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("SecurityFrozen")).toBool();
}

bool UDisksDriveAta::smartEnabled() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("SmartEnabled")).toBool();
}

bool UDisksDriveAta::smartFailing() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("SmartFailing")).toBool();
}

int UDisksDriveAta::smartNumAttributesFailedInThePast() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("SmartNumAttributesFailedInThePast")).toInt();
}

int UDisksDriveAta::smartNumAttributesFailing() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("SmartNumAttributesFailing")).toInt();
}

qlonglong UDisksDriveAta::smartNumBadSectors() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("SmartNumBadSectors")).toLongLong();
}

qulonglong UDisksDriveAta::smartPowerOnSeconds() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("SmartPowerOnSeconds")).toULongLong();
}

int UDisksDriveAta::smartSelftestPercentRemaining() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("SmartSelftestPercentRemaining")).toInt();
}

QString UDisksDriveAta::smartSelftestStatus() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("SmartSelftestStatus")).toString();
}

bool UDisksDriveAta::smartSupported() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("SmartSupported")).toBool();
}

double UDisksDriveAta::smartTemperature() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("SmartTemperature")).toDouble();
}

qulonglong UDisksDriveAta::smartUpdated() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("SmartUpdated")).toULongLong();
}

bool UDisksDriveAta::writeCacheEnabled() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("WriteCacheEnabled")).toBool();
}

bool UDisksDriveAta::writeCacheSupported() const
{
    Q_D(const UDisksDriveAta);
    return d->properties.value(QStringLiteral("WriteCacheSupported")).toBool();
}

QDBusPendingReply<uchar> UDisksDriveAta::pmGetState(const QVariantMap &options)
{
    Q_D(UDisksDriveAta);
    return d->interface.PmGetState(options);
}

QDBusPendingReply<> UDisksDriveAta::pmStandby(const QVariantMap &options)
{
    Q_D(UDisksDriveAta);
    return d->interface.PmStandby(options);
}

QDBusPendingReply<> UDisksDriveAta::pmWakeup(const QVariantMap &options)
{
    Q_D(UDisksDriveAta);
    return d->interface.PmWakeup(options);
}

QDBusPendingReply<> UDisksDriveAta::securityEraseUnit(const QVariantMap &options)
{
    Q_D(UDisksDriveAta);
    return d->interface.SecurityEraseUnit(options);
}

QDBusPendingReply<UDisksAttributes> UDisksDriveAta::smartGetAttributes(const QVariantMap &options)
{
    Q_D(UDisksDriveAta);
    return d->interface.SmartGetAttributes(options);
}

QDBusPendingReply<> UDisksDriveAta::smartSelftestAbort(const QVariantMap &options)
{
    Q_D(UDisksDriveAta);
    return d->interface.SmartSelftestAbort(options);
}

QDBusPendingReply<> UDisksDriveAta::smartSelftestStart(const QString &type, const QVariantMap &options)
{
    Q_D(UDisksDriveAta);
    return d->interface.SmartSelftestStart(type, options);
}

QDBusPendingReply<> UDisksDriveAta::smartSetEnabled(bool value, const QVariantMap &options)
{
    Q_D(UDisksDriveAta);
    return d->interface.SmartSetEnabled(value, options);
}

QDBusPendingReply<> UDisksDriveAta::smartUpdate(const QVariantMap &options)
{
    Q_D(UDisksDriveAta);
    return d->interface.SmartUpdate(options);
}

void UDisksDriveAta::propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties)
{
    Q_D(UDisksDriveAta);
    changeProperties(d->properties, properties, invalidProperties);
}

UDisksDriveAtaPrivate::UDisksDriveAtaPrivate(const QString &path) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus())
{
}
