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

UDisksDriveAta::UDisksDriveAta(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties, QObject *parent) :
    QObject(parent),
    d_ptr(new UDisksDriveAtaPrivate(objectPath.path()))
{
    Q_D(UDisksDriveAta);

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

bool UDisksDriveAta::aamEnabled() const
{
    Q_D(const UDisksDriveAta);
    return d->aamEnabled;
}

bool UDisksDriveAta::aamSupported() const
{
    Q_D(const UDisksDriveAta);
    return d->aamSupported;
}

int UDisksDriveAta::aamVendorRecommendedValue() const
{
    Q_D(const UDisksDriveAta);
    return d->aamVendorRecommendedValue;
}

bool UDisksDriveAta::apmEnabled() const
{
    Q_D(const UDisksDriveAta);
    return d->apmEnabled;
}

bool UDisksDriveAta::apmSupported() const
{
    Q_D(const UDisksDriveAta);
    return d->apmSupported;
}

bool UDisksDriveAta::pmEnabled() const
{
    Q_D(const UDisksDriveAta);
    return d->pmEnabled;
}

bool UDisksDriveAta::pmSupported() const
{
    Q_D(const UDisksDriveAta);
    return d->pmSupported;
}

int UDisksDriveAta::securityEnhancedEraseUnitMinutes() const
{
    Q_D(const UDisksDriveAta);
    return d->securityEnhancedEraseUnitMinutes;
}

int UDisksDriveAta::securityEraseUnitMinutes() const
{
    Q_D(const UDisksDriveAta);
    return d->securityEraseUnitMinutes;
}

bool UDisksDriveAta::securityFrozen() const
{
    Q_D(const UDisksDriveAta);
    return d->securityFrozen;
}

bool UDisksDriveAta::smartEnabled() const
{
    Q_D(const UDisksDriveAta);
    return d->smartEnabled;
}

bool UDisksDriveAta::smartFailing() const
{
    Q_D(const UDisksDriveAta);
    return d->smartFailing;
}

int UDisksDriveAta::smartNumAttributesFailedInThePast() const
{
    Q_D(const UDisksDriveAta);
    return d->smartNumAttributesFailedInThePast;
}

int UDisksDriveAta::smartNumAttributesFailing() const
{
    Q_D(const UDisksDriveAta);
    return d->smartNumAttributesFailing;
}

qlonglong UDisksDriveAta::smartNumBadSectors() const
{
    Q_D(const UDisksDriveAta);
    return d->smartNumBadSectors;
}

qulonglong UDisksDriveAta::smartPowerOnSeconds() const
{
    Q_D(const UDisksDriveAta);
    return d->smartPowerOnSeconds;
}

int UDisksDriveAta::smartSelftestPercentRemaining() const
{
    Q_D(const UDisksDriveAta);
    return d->smartSelftestPercentRemaining;
}

QString UDisksDriveAta::smartSelftestStatus() const
{
    Q_D(const UDisksDriveAta);
    return d->smartSelftestStatus;
}

bool UDisksDriveAta::smartSupported() const
{
    Q_D(const UDisksDriveAta);
    return d->smartSupported;
}

double UDisksDriveAta::smartTemperature() const
{
    Q_D(const UDisksDriveAta);
    return d->smartTemperature;
}

qulonglong UDisksDriveAta::smartUpdated() const
{
    Q_D(const UDisksDriveAta);
    return d->smartUpdated;
}

bool UDisksDriveAta::writeCacheEnabled() const
{
    Q_D(const UDisksDriveAta);
    return d->writeCacheEnabled;
}

bool UDisksDriveAta::writeCacheSupported() const
{
    Q_D(const UDisksDriveAta);
    return d->writeCacheSupported;
}

UDisksDriveAtaPrivate::UDisksDriveAtaPrivate(const QString &path) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus())
{
}

void UDisksDriveAtaPrivate::init(const QVariantMap &properties)
{
    QVariantMap::ConstIterator it = properties.constBegin();
    while (it != properties.constEnd()) {
        const QString &property = it.key();
        const QVariant &value = it.value();
        qDebug() << Q_FUNC_INFO << property << value;

        if (property == QLatin1String("AamEnabled")) {
            aamEnabled = value.toBool();
        } else if (property == QLatin1String("AamSupported")) {
            aamSupported = value.toBool();
        } else if (property == QLatin1String("AamVendorRecommendedValue")) {
            aamVendorRecommendedValue = value.toInt();
        } else if (property == QLatin1String("ApmEnabled")) {
            apmEnabled = value.toBool();
        } else if (property == QLatin1String("ApmSupported")) {
            apmSupported = value.toBool();
        } else if (property == QLatin1String("PmEnabled")) {
            pmEnabled = value.toBool();
        } else if (property == QLatin1String("PmSupported")) {
            pmSupported = value.toBool();
        } else if (property == QLatin1String("SecurityEnhancedEraseUnitMinutes")) {
            securityEnhancedEraseUnitMinutes = value.toInt();
        } else if (property == QLatin1String("SecurityEraseUnitMinutes")) {
            securityEraseUnitMinutes = value.toInt();
        } else if (property == QLatin1String("SecurityFrozen")) {
            securityFrozen = value.toBool();
        } else if (property == QLatin1String("SmartEnabled")) {
            smartEnabled = value.toBool();
        } else if (property == QLatin1String("SmartFailing")) {
            smartFailing = value.toBool();
        } else if (property == QLatin1String("SmartNumAttributesFailedInThePast")) {
            smartNumAttributesFailedInThePast = value.toInt();
        } else if (property == QLatin1String("SmartNumAttributesFailing")) {
            smartNumAttributesFailing = value.toInt();
        } else if (property == QLatin1String("SmartNumBadSectors")) {
            smartNumBadSectors = value.toULongLong();
        } else if (property == QLatin1String("SmartPowerOnSeconds")) {
            smartPowerOnSeconds = value.toULongLong();
        } else if (property == QLatin1String("SmartSelftestPercentRemaining")) {
            smartSelftestPercentRemaining = value.toInt();
        } else if (property == QLatin1String("SmartSelftestStatus")) {
            smartSelftestStatus = value.toString();
        } else if (property == QLatin1String("SmartSupported")) {
            smartSupported = value.toBool();
        } else if (property == QLatin1String("SmartTemperature")) {
            smartTemperature = value.toDouble();
        } else if (property == QLatin1String("SmartUpdated")) {
            smartUpdated = value.toULongLong();
        } else if (property == QLatin1String("WriteCacheEnabled")) {
            writeCacheEnabled = value.toBool();
        } else if (property == QLatin1String("WriteCacheSupported")) {
            writeCacheSupported = value.toBool();
        } else {
            qWarning() << Q_FUNC_INFO << "Unknown property, please report a bug:" << property << value;
        }

        ++it;
    }
}
