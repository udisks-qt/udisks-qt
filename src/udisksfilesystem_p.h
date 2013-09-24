#ifndef UDISKSFILESYSTEM_P_H
#define UDISKSFILESYSTEM_P_H

#include "UDisks.h"

class UDisksFilesystemPrivate
{
public:
    UDisksFilesystemPrivate(const QString &path);

    OrgFreedesktopUDisks2FilesystemInterface interface;
    QVariantMap properties;
};

#endif // UDISKSFILESYSTEM_P_H
