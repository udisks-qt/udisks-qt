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
    d_ptr(new UDisksClientPrivate)
{
}

bool UDisksClient::init(bool async)
{
    Q_D(UDisksClient);

    if (async) {
        QDBusPendingReply<UDManagedObjects> reply = d->objectInterface.GetManagedObjects();
        QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(reply, this);

//        QObject::connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
//                         d, SLOT(callFinishedSlot(QDBusPendingCallWatcher*)));
    } else {
        QDBusReply<UDManagedObjects> reply = d->objectInterface.GetManagedObjects();
        if (reply.isValid()) {
            return false;
        }


    }
    return true;
}

UDisksClientPrivate::UDisksClientPrivate() :
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

void UDisksClientPrivate::init(const QVariantMap &properties)
{
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

void UDisksClientPrivate::_q_interfacesAdded(const QDBusObjectPath &object_path, UDVariantMapMap interfaces_and_properties)
{
    UDisksObject::Ptr object(new UDisksObject(object_path, interfaces_and_properties));
    objects << object;
}

#include "moc_udisksclient.cpp"
