#ifndef UDisksDriveAtaATA_P_H
#define UDisksDriveAtaATA_P_H

#include "UDisks.h"

class UDisksDriveAtaPrivate
{
public:
    UDisksDriveAtaPrivate(const QString &path);
    void init(const QVariantMap &properties);

    OrgFreedesktopUDisks2DriveAtaInterface interface;

    bool aamEnabled;
    bool aamSupported;
    int aamVendorRecommendedValue;
    bool apmEnabled;
    bool apmSupported;
    bool pmEnabled;
    bool pmSupported;
    int securityEnhancedEraseUnitMinutes;
    int securityEraseUnitMinutes;
    bool securityFrozen;
    bool smartEnabled;
    bool smartFailing;
    int smartNumAttributesFailedInThePast;
    int smartNumAttributesFailing;
    qlonglong smartNumBadSectors;
    qulonglong smartPowerOnSeconds;
    int smartSelftestPercentRemaining;
    QString smartSelftestStatus;
    bool smartSupported;
    double smartTemperature;
    qulonglong smartUpdated;
    bool writeCacheEnabled;
    bool writeCacheSupported;
};

#endif // UDisksDriveAtaATA_P_H
