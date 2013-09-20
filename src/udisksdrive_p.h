#ifndef UDISKSDRIVE_P_H
#define UDISKSDRIVE_P_H

#include "UDisks.h"

class UDisksDrivePrivate
{
public:
    UDisksDrivePrivate(const QString &path);
    void init(const QVariantMap &properties);

    OrgFreedesktopUDisks2DriveInterface interface;

    bool canPowerOff;
    QVariantMap configuration;
    QString connectionBus;
    bool ejectable;
    QString id;
    QString media;
    bool mediaAvailable;
    bool mediaChangeDetected;
    QStringList mediaCompatibility;
    bool mediaRemovable;
    QString model;
    bool optical;
    bool opticalBlank;
    uint opticalNumAudioTracks;
    uint opticalNumDataTracks;
    uint opticalNumSessions;
    uint opticalNumTracks;
    bool removable;
    QString revision;
    int rotationRate;
    QString seat;
    QString serial;
    QString siblingId;
    qulonglong size;
    QString sortKey;
    qulonglong timeDetected;
    qulonglong timeMediaDetected;
    QString vendor;
    QString wWN;
};

#endif // UDISKSDRIVE_P_H
