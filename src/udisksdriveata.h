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

#ifndef UDisksDriveAtaATA_H
#define UDisksDriveAtaATA_H

#include <QObject>

#include "dbus-types.h"

class UDisksDriveAtaPrivate;
class UDisksDriveAta : public QObject
{
    Q_OBJECT
public:
    explicit UDisksDriveAta(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties, QObject *parent = 0);

    Q_PROPERTY(bool AamEnabled READ aamEnabled)
    bool aamEnabled() const;

    Q_PROPERTY(bool AamSupported READ aamSupported)
    bool aamSupported() const;

    Q_PROPERTY(int AamVendorRecommendedValue READ aamVendorRecommendedValue)
    int aamVendorRecommendedValue() const;

    Q_PROPERTY(bool ApmEnabled READ apmEnabled)
    bool apmEnabled() const;

    Q_PROPERTY(bool ApmSupported READ apmSupported)
    bool apmSupported() const;

    Q_PROPERTY(bool PmEnabled READ pmEnabled)
    bool pmEnabled() const;

    Q_PROPERTY(bool PmSupported READ pmSupported)
    bool pmSupported() const;

    Q_PROPERTY(int SecurityEnhancedEraseUnitMinutes READ securityEnhancedEraseUnitMinutes)
    int securityEnhancedEraseUnitMinutes() const;

    Q_PROPERTY(int SecurityEraseUnitMinutes READ securityEraseUnitMinutes)
    int securityEraseUnitMinutes() const;

    Q_PROPERTY(bool SecurityFrozen READ securityFrozen)
    bool securityFrozen() const;

    Q_PROPERTY(bool SmartEnabled READ smartEnabled)
    bool smartEnabled() const;

    Q_PROPERTY(bool SmartFailing READ smartFailing)
    bool smartFailing() const;

    Q_PROPERTY(int SmartNumAttributesFailedInThePast READ smartNumAttributesFailedInThePast)
    int smartNumAttributesFailedInThePast() const;

    Q_PROPERTY(int SmartNumAttributesFailing READ smartNumAttributesFailing)
    int smartNumAttributesFailing() const;

    Q_PROPERTY(qlonglong SmartNumBadSectors READ smartNumBadSectors)
    qlonglong smartNumBadSectors() const;

    Q_PROPERTY(qulonglong SmartPowerOnSeconds READ smartPowerOnSeconds)
    qulonglong smartPowerOnSeconds() const;

    Q_PROPERTY(int SmartSelftestPercentRemaining READ smartSelftestPercentRemaining)
    int smartSelftestPercentRemaining() const;

    Q_PROPERTY(QString SmartSelftestStatus READ smartSelftestStatus)
    QString smartSelftestStatus() const;

    Q_PROPERTY(bool SmartSupported READ smartSupported)
    bool smartSupported() const;

    Q_PROPERTY(double SmartTemperature READ smartTemperature)
    double smartTemperature() const;

    Q_PROPERTY(qulonglong SmartUpdated READ smartUpdated)
    qulonglong smartUpdated() const;

    Q_PROPERTY(bool WriteCacheEnabled READ writeCacheEnabled)
    bool writeCacheEnabled() const;

    Q_PROPERTY(bool WriteCacheSupported READ writeCacheSupported)
    bool writeCacheSupported() const;

protected:
    UDisksDriveAtaPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksDriveAta)
};

#endif // UDisksDriveAtaATA_H
