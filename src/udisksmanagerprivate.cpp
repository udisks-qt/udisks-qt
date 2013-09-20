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

#include "udisksmanagerprivate.h"
#include "common.h"

#include "UDisks.h"
#include "DBusObjectManager.h"

#include <QtDBus/QDBusConnection>

UDisksManagerPrivate::UDisksManagerPrivate(UDisksManager *parent) :
    q_ptr(parent)
{
    qDBusRegisterMetaType<UDVariantMapMap>();
    qDBusRegisterMetaType<UDManagedObjects>();
    qDBusRegisterMetaType<UDItem>();
    qDBusRegisterMetaType<UDItemList>();
    qDBusRegisterMetaType<UDAttributes>();
    qDBusRegisterMetaType<UDActiveDevice>();

    interface = new OrgFreedesktopUDisks2ManagerInterface(QLatin1String(UD2_SERVICE),
                                                          QLatin1String(UD2_PATH_MANAGER),
                                                          QDBusConnection::systemBus(),
                                                          parent);
    running = interface->isValid();

    objectInterface = new OrgFreedesktopDBusObjectManagerInterface(QLatin1String(UD2_SERVICE),
                                                                   QLatin1String(UD2_PATH),
                                                                   QDBusConnection::systemBus(),
                                                                   parent);

    m_watcher = new QDBusServiceWatcher(QLatin1String(UD2_SERVICE),
                                        QDBusConnection::systemBus(),
                                        QDBusServiceWatcher::WatchForOwnerChange,
                                        parent);
    QObject::connect(m_watcher, SIGNAL(serviceOwnerChanged(QString,QString,QString)),
                     q_ptr, SLOT(serviceOwnerChanged(QString,QString,QString)));

    if (running) {
        // init objects
        init();
    } else {
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

void UDisksManagerPrivate::init()
{
    Q_Q(UDisksManager);

    QDBusPendingReply<UDManagedObjects> reply = objectInterface->GetManagedObjects();
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(reply, q);

    QObject::connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
                     q, SLOT(callFinishedSlot(QDBusPendingCallWatcher*)));
}
