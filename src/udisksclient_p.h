#ifndef UDISKSCLIENT_P_H
#define UDISKSCLIENT_P_H

#include "udisksclient.h"

#include "DBusObjectManager.h"
#include "udisksobject.h"

#include <QtDBus/QDBusServiceWatcher>

class UDisksClientPrivate
{
    Q_DECLARE_PUBLIC(UDisksClient)
public:
    UDisksClientPrivate();
    void init(const QVariantMap &properties);
    void initObjects(const UDManagedObjects &managedObjects);

    void _q_interfacesAdded(const QDBusObjectPath &object_path, UDVariantMapMap interfaces_and_properties);

    OrgFreedesktopDBusObjectManagerInterface objectInterface;
    QDBusServiceWatcher *watcher;
    UDisksObject::List objects;
    UDisksClient *q_ptr;
};

#endif // UDISKSCLIENT_P_H
