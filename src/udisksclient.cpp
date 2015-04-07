/*
 * Copyright (C) 2013 Daniel Nicoletti <dantti12@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "udisksclient_p.h"

#include "udiskspartition.h"
#include "common.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(UDISKSQT_CLIENT, "udisksqt.client")

UDisksClient::UDisksClient(QObject *parent) :
    QObject(parent),
    d_ptr(new UDisksClientPrivate(this))
{
}

UDisksClient::~UDisksClient()
{
    delete d_ptr;
}

bool UDisksClient::inited() const
{
    Q_D(const UDisksClient);
    return d->inited;
}

bool UDisksClient::init(bool async)
{
    Q_D(UDisksClient);

    if (d->inited) {
        return true;
    }

    connect(&d->objectInterface, SIGNAL(InterfacesAdded(QDBusObjectPath,UDVariantMapMap)),
            SLOT(_q_interfacesAdded(QDBusObjectPath,UDVariantMapMap)));
    connect(&d->objectInterface, SIGNAL(InterfacesRemoved(QDBusObjectPath,QStringList)),
            SLOT(_q_interfacesRemoved(QDBusObjectPath,QStringList)));

    if (async) {
        QDBusPendingReply<UDManagedObjects> reply = d->objectInterface.GetManagedObjects();
        QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(reply, this);
        connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                SLOT(_q_getObjectsFinished(QDBusPendingCallWatcher*)));
    } else {
        QDBusReply<UDManagedObjects> reply = d->objectInterface.GetManagedObjects();
        d->inited = true;

        if (!reply.isValid()) {
            qCWarning(UDISKSQT_CLIENT) << Q_FUNC_INFO << reply.error().message();
            return false;
        }

        d->initObjects(reply.value());
    }
    return true;
}

UDisksObject::List UDisksClient::getObjects(UDisksObject::Kind kind) const
{
    Q_D(const UDisksClient);

    if (kind == UDisksObject::Any) {
        return d->objects.values();
    } else {
        UDisksObject::List ret;
        QHash<QDBusObjectPath, UDisksObject::Ptr>::ConstIterator it = d->objects.constBegin();
        while (it != d->objects.end()) {
            if (kind == it.value()->kind()) {
                ret << it.value();
            }
            ++it;
        }
        return ret;
    }
}

UDisksObject::List UDisksClient::getObjects(const QList<QDBusObjectPath> &objectPaths) const
{
    Q_D(const UDisksClient);
    UDisksObject::List ret;
    foreach (const QDBusObjectPath &objectPath, objectPaths) {
        UDisksObject::Ptr object = d->objects.value(objectPath);
        if (object) {
            ret << object;
        }
    }
    return ret;
}

UDisksObject::Ptr UDisksClient::getObject(const QDBusObjectPath &objectPath) const
{
    Q_D(const UDisksClient);
    return d->objects.value(objectPath);
}

UDisksObject::List UDisksClient::getPartitions(const QDBusObjectPath &tablePath) const
{
    UDisksObject::List ret;
    UDisksObject::List blockDevices = getObjects(UDisksObject::BlockDevice);
    foreach (const UDisksObject::Ptr &object, blockDevices) {
        if (object->partition() && object->partition()->table() == tablePath) {
            ret << object;
        }
    }
    return ret;
}

UDisksManager *UDisksClient::manager() const
{
    UDisksManager *ret = 0;
    UDisksObject::List managers = getObjects(UDisksObject::Manager);
    if (!managers.isEmpty()) {
        ret = managers.first()->manager();
    }
    return ret;
}

UDisksClientPrivate::UDisksClientPrivate(UDisksClient *parent) :
    q_ptr(parent),
    inited(false),
    objectInterface(QLatin1String(UD2_SERVICE),
                    QLatin1String(UD2_PATH),
                    QDBusConnection::systemBus())
{
    qDBusRegisterMetaType<UDVariantMapMap>();
    qDBusRegisterMetaType<UDManagedObjects>();
    qDBusRegisterMetaType<UDItem>();
    qDBusRegisterMetaType<UDItemList>();
    qDBusRegisterMetaType<UDAttributes>();
    qDBusRegisterMetaType<UDActiveDevice>();
    qDBusRegisterMetaType<UDByteArrayList>();

    watcher = new QDBusServiceWatcher(QLatin1String(UD2_SERVICE),
                                      QDBusConnection::systemBus(),
                                      QDBusServiceWatcher::WatchForOwnerChange);
//    QObject::connect(watcher, SIGNAL(serviceOwnerChanged(QString,QString,QString)),
//                     q_ptr, SLOT(serviceOwnerChanged(QString,QString,QString)));

    if (!objectInterface.isValid()) {
        // TODO do an async call
        QDBusMessage message;
        message = QDBusMessage::createMethodCall(QLatin1String("org.freedesktop.DBus"),
                                                 QLatin1String("/org/freedesktop/DBus"),
                                                 QLatin1String("org.freedesktop.DBus"),
                                                 QLatin1String("ListActivatableNames"));

        QDBusReply<QStringList> reply = QDBusConnection::systemBus().call(message);
        if (reply.isValid() && reply.value().contains(QLatin1String(UD2_SERVICE))) {
            QDBusConnection::systemBus().interface()->startService(QLatin1String(UD2_SERVICE));
        } else {
            qCWarning(UDISKSQT_CLIENT) << "UDisk2 service is not available, check if it's properly installed";
        }
    }
}

void UDisksClientPrivate::initObjects(const UDManagedObjects &managedObjects)
{
    Q_Q(UDisksClient);

    UDManagedObjects::ConstIterator it = managedObjects.constBegin();
    while (it != managedObjects.constEnd()) {
        UDisksObject::Ptr object(new UDisksObject(it.key(), it.value(), q));
        objects.insert(it.key(), object);
        ++it;
    }
}

void UDisksClientPrivate::_q_getObjectsFinished(QDBusPendingCallWatcher *call)
{
    Q_Q(UDisksClient);
//    qWarning() << Q_FUNC_INFO;
    QDBusPendingReply<UDManagedObjects> reply = *call;
    if (reply.isError()) {
//        showError();
        qCWarning(UDISKSQT_CLIENT) << Q_FUNC_INFO << reply.error().message();
    } else {
        initObjects(reply.value());
    }
    call->deleteLater();

    inited = true;
    q->objectsAvailable();
}

void UDisksClientPrivate::_q_interfacesAdded(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties)
{
    Q_Q(UDisksClient);

    qCDebug(UDISKSQT_CLIENT) << Q_FUNC_INFO << objectPath.path();

    UDisksObject::Ptr object = objects.value(objectPath);
    if (object.isNull()) {
        UDisksObject::Ptr object(new UDisksObject(objectPath, interfacesAndProperties, q));
        objects.insert(objectPath, object);
        q->objectAdded(object);
    } else {
        object->addInterfaces(interfacesAndProperties);
        q->interfacesAdded(object);
    }
}

void UDisksClientPrivate::_q_interfacesRemoved(const QDBusObjectPath &objectPath, const QStringList &interfaces)
{
    Q_Q(UDisksClient);

    qCDebug(UDISKSQT_CLIENT) << Q_FUNC_INFO << objectPath.path();

    UDisksObject::Ptr object = objects.value(objectPath);
    if (object) {
        object->removeInterfaces(interfaces);
        if (object->interfaces() == UDisksObject::InterfaceNone) {
            q->objectRemoved(object);
            objects.remove(objectPath);
        } else {
            q->interfacesRemoved(object);
        }
    }
}

#include "moc_udisksclient.cpp"
