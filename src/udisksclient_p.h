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
    UDisksClientPrivate(UDisksClient *parent);
    void initObjects(const UDManagedObjects &managedObjects);

    void _q_getObjectsFinished(QDBusPendingCallWatcher *call);
    void _q_interfacesAdded(const QDBusObjectPath &object_path, UDVariantMapMap interfaces_and_properties);
    void _q_interfacesRemoved(const QDBusObjectPath &object_path, const QStringList &interfaces);

    UDisksClient *q_ptr;
    bool inited;
    OrgFreedesktopDBusObjectManagerInterface objectInterface;
    QDBusServiceWatcher *watcher;
    UDisksObject::List objects;
};

#endif // UDISKSCLIENT_P_H
