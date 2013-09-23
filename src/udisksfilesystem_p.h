#ifndef UDISKSFILESYSTEM_P_H
#define UDISKSFILESYSTEM_P_H

#include "UDisks.h"

class UDisksFilesytemPrivate
{
public:
    UDisksFilesytemPrivate(const QString &path);
    void init(const QVariantMap &properties);

    OrgFreedesktopUDisks2FilesystemInterface interface;

    QVariantMap properties;
};

#endif // UDISKSFILESYSTEM_P_H
