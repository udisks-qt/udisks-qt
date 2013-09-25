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
    void _q_interfacesAdded(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties);
    void _q_interfacesRemoved(const QDBusObjectPath &objectPath, const QStringList &interfaces);

    UDisksClient *q_ptr;
    bool inited;
    OrgFreedesktopDBusObjectManagerInterface objectInterface;
    QDBusServiceWatcher *watcher;
    QHash<QDBusObjectPath, UDisksObject::Ptr> objects;
};

#endif // UDISKSCLIENT_P_H
