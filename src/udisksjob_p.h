#ifndef UDISKSJOB_P_H
#define UDISKSJOB_P_H

#include "UDisks.h"

class UDisksJobPrivate
{
public:
    UDisksJobPrivate(const QString &path);
    void init(const QVariantMap &properties);

    OrgFreedesktopUDisks2JobInterface interface;

    QVariantMap properties;
};

#endif // UDISKSJOB_P_H
