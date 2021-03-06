#ifndef UDISKSCLIENT_P_H
#define UDISKSCLIENT_P_H

#include "udisksclient.h"

#include "DBusObjectManager.h"
#include "udisksobject.h"

#include <QtDBus/QDBusServiceWatcher>

class UDisksClientPrivate
{
public:
    UDisksClientPrivate();
    void initObjects(const UDisksManagedObjects &managedObjects, UDisksClient *client);

    bool inited = false;
    OrgFreedesktopDBusObjectManagerInterface objectInterface;
    QHash<QDBusObjectPath, UDisksObject::Ptr> objects;
};

#endif // UDISKSCLIENT_P_H
