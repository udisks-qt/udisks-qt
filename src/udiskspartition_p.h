#ifndef UDISKSPARTITION_P_H
#define UDISKSPARTITION_P_H

#include "UDisks.h"

class UDisksPartitionPrivate
{
public:
    UDisksPartitionPrivate(const QString &path);
    void init(const QVariantMap &properties);

    OrgFreedesktopUDisks2PartitionInterface interface;

    qulonglong flags;
    bool isContained;
    bool isContainer;
    QString name;
    uint number;
    qulonglong offset;
    qulonglong size;
    QDBusObjectPath table;
    QString type;
    QString uUID;
};

#endif // UDISKSPARTITION_P_H
