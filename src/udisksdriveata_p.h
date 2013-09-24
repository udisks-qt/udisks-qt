#ifndef UDisksDriveAtaATA_P_H
#define UDisksDriveAtaATA_P_H

#include "UDisks.h"

class UDisksDriveAtaPrivate
{
public:
    UDisksDriveAtaPrivate(const QString &path);

    OrgFreedesktopUDisks2DriveAtaInterface interface;
    QVariantMap properties;
};

#endif // UDisksDriveAtaATA_P_H
