#ifndef UDISKSENCRYPTED_P_H
#define UDISKSENCRYPTED_P_H

#include "UDisks.h"

class UDisksEncryptedPrivate
{
public:
    UDisksEncryptedPrivate(const QString &path);

    OrgFreedesktopUDisks2EncryptedInterface interface;
    QVariantMap properties;
};

#endif // UDISKSENCRYPTED_P_H
