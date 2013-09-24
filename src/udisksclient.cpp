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

#include "common.h"

#include <QDebug>

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
            SLOT(_q_interfacesAdded(QDBusObjectPath,QStringList)));

    if (async) {
        QDBusPendingReply<UDManagedObjects> reply = d->objectInterface.GetManagedObjects();
        QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(reply, this);
        connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                SLOT(_q_getObjectsFinished(QDBusPendingCallWatcher*)));
    } else {
        QDBusReply<UDManagedObjects> reply = d->objectInterface.GetManagedObjects();
        d->inited = true;

        if (!reply.isValid()) {
            qWarning() << Q_FUNC_INFO << reply.error().message();
            return false;
        }

        d->initObjects(reply.value());
    }
    return true;
}

UDisksObject::List UDisksClient::getObjects(UDisksObject::Kind kind)
{
    Q_D(const UDisksClient);

    if (kind == UDisksObject::Any) {
        return d->objects;
    } else {
        UDisksObject::List ret;
        foreach (const UDisksObject::Ptr &object, d->objects) {
            if (kind == object->kind()) {
                ret << object;
            }
        }
        return ret;
    }
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
            qWarning() << "UDisk2 service is not available, check if it's properly installed";
        }
    }
}

void UDisksClientPrivate::initObjects(const UDManagedObjects &managedObjects)
{
    UDManagedObjects::ConstIterator it = managedObjects.constBegin();
    while (it != managedObjects.constEnd()) {
        UDisksObject::Ptr object(new UDisksObject(it.key(), it.value()));
        objects << object;
        ++it;
    }
}

void UDisksClientPrivate::_q_getObjectsFinished(QDBusPendingCallWatcher *call)
{
    Q_Q(UDisksClient);
    qWarning() << Q_FUNC_INFO;
    QDBusPendingReply<UDManagedObjects> reply = *call;
    if (reply.isError()) {
//        showError();
        qWarning() << Q_FUNC_INFO << reply.error().message();
    } else {
        initObjects(reply.value());
    }
    call->deleteLater();

    inited = true;
    q->objectsAvailable();
}

void UDisksClientPrivate::_q_interfacesAdded(const QDBusObjectPath &object_path, UDVariantMapMap interfaces_and_properties)
{
    Q_Q(UDisksClient);

    foreach (const UDisksObject::Ptr &object, objects) {
        if (object->path() == object_path) {
            object->addInterfaces(interfaces_and_properties);
            q->interfacesAdded(object);
            return;
        }
    }

    UDisksObject::Ptr object(new UDisksObject(object_path, interfaces_and_properties));
    objects << object;
    q->objectAdded(object);
}

void UDisksClientPrivate::_q_interfacesRemoved(const QDBusObjectPath &object_path, const QStringList &interfaces)
{
    Q_Q(UDisksClient);

    foreach (const UDisksObject::Ptr &object, objects) {
        if (object->path() == object_path) {
            object->removeInterfaces(interfaces);
            q->interfacesRemoved(object);
            return;
        }
    }
}

#include "moc_udisksclient.cpp"
