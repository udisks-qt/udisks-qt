#ifndef UDISKSDRIVE_P_H
#define UDISKSDRIVE_P_H

#include "UDisks.h"

class UDisksDrivePrivate
{
public:
    UDisksDrivePrivate(const QString &path, const QVariantMap &propertiesMap);

    static UDisksObject::List topLevelBlocks(UDisksClient *client, const QString &driveObjectPath);

    OrgFreedesktopUDisks2DriveInterface interface;
    QVariantMap properties;
};

#endif // UDISKSDRIVE_P_H
