#ifndef UDISKSLOOP_P_H
#define UDISKSLOOP_P_H

#include "UDisks.h"

class UDisksLoopPrivate
{
public:
    UDisksLoopPrivate(const QString &path);
    void init(const QVariantMap &properties);

    OrgFreedesktopUDisks2LoopInterface interface;

    QVariantMap properties;
};

#endif // UDISKSLOOP_P_H
