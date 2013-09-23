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

    Q_PROPERTY(bool aamEnabled READ aamEnabled)
    bool aamEnabled() const;

    Q_PROPERTY(bool aamSupported READ aamSupported)
    bool aamSupported() const;

    Q_PROPERTY(int aamVendorRecommendedValue READ aamVendorRecommendedValue)
    int aamVendorRecommendedValue() const;

    Q_PROPERTY(bool apmEnabled READ apmEnabled)
    bool apmEnabled() const;

    Q_PROPERTY(bool apmSupported READ apmSupported)
    bool apmSupported() const;

    Q_PROPERTY(bool pmEnabled READ pmEnabled)
    bool pmEnabled() const;

    Q_PROPERTY(bool pmSupported READ pmSupported)
    bool pmSupported() const;

    Q_PROPERTY(int securityEnhancedEraseUnitMinutes READ securityEnhancedEraseUnitMinutes)
    int securityEnhancedEraseUnitMinutes() const;

    Q_PROPERTY(int securityEraseUnitMinutes READ securityEraseUnitMinutes)
    int securityEraseUnitMinutes() const;

    Q_PROPERTY(bool securityFrozen READ securityFrozen)
    bool securityFrozen() const;

    Q_PROPERTY(bool smartEnabled READ smartEnabled)
    bool smartEnabled() const;

    Q_PROPERTY(bool smartFailing READ smartFailing)
    bool smartFailing() const;

    Q_PROPERTY(int smartNumAttributesFailedInThePast READ smartNumAttributesFailedInThePast)
    int smartNumAttributesFailedInThePast() const;

    Q_PROPERTY(int smartNumAttributesFailing READ smartNumAttributesFailing)
    int smartNumAttributesFailing() const;

    Q_PROPERTY(qlonglong smartNumBadSectors READ smartNumBadSectors)
    qlonglong smartNumBadSectors() const;

    Q_PROPERTY(qulonglong smartPowerOnSeconds READ smartPowerOnSeconds)
    qulonglong smartPowerOnSeconds() const;

    Q_PROPERTY(int smartSelftestPercentRemaining READ smartSelftestPercentRemaining)
    int smartSelftestPercentRemaining() const;

    Q_PROPERTY(QString smartSelftestStatus READ smartSelftestStatus)
    QString smartSelftestStatus() const;

    Q_PROPERTY(bool smartSupported READ smartSupported)
    bool smartSupported() const;

    Q_PROPERTY(double smartTemperature READ smartTemperature)
    double smartTemperature() const;

    Q_PROPERTY(qulonglong smartUpdated READ smartUpdated)
    qulonglong smartUpdated() const;

    Q_PROPERTY(bool writeCacheEnabled READ writeCacheEnabled)
    bool writeCacheEnabled() const;

    Q_PROPERTY(bool writeCacheSupported READ writeCacheSupported)
    bool writeCacheSupported() const;

protected:
    UDisksDriveAtaPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksDriveAta)
};

#endif // UDisksDriveAtaATA_H
