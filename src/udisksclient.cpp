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
    d_ptr(new UDisksClientPrivate)
{
    Q_D(UDisksClient);

    connect(&d->objectInterface, &OrgFreedesktopDBusObjectManagerInterface::InterfacesAdded,
            this, [=] (const QDBusObjectPath & objectPath, UDVariantMapMap interfacesAndProperties) {
        qCDebug(UDISKSQT_CLIENT) << "interfaces added" << objectPath.path();

        UDisksObject::Ptr object = d->objects.value(objectPath);
        if (object.isNull()) {
            UDisksObject::Ptr object(new UDisksObject(objectPath, interfacesAndProperties, this));
            d->objects.insert(objectPath, object);
            Q_EMIT objectAdded(object);
        } else {
            object->addInterfaces(interfacesAndProperties);
            Q_EMIT interfacesAdded(object);
        }
    });
    connect(&d->objectInterface, &OrgFreedesktopDBusObjectManagerInterface::InterfacesRemoved,
            this, [=] (const QDBusObjectPath & objectPath, const QStringList &interfaces) {
        qCDebug(UDISKSQT_CLIENT) << "interfaces removed" << objectPath.path();

        auto it = d->objects.find(objectPath);
        if (it != d->objects.end() && !it.value().isNull()) {
            UDisksObject::Ptr object = it.value();
            it.value()->removeInterfaces(interfaces);
            if (object->interfaces() == UDisksObject::InterfaceNone) {
                Q_EMIT objectRemoved(object);
                d->objects.erase(it);
            } else {
                Q_EMIT interfacesRemoved(object);
            }
        }
    });

    auto watcher = new QDBusServiceWatcher(QStringLiteral(UD2_SERVICE),
                                           QDBusConnection::systemBus(),
                                           QDBusServiceWatcher::WatchForUnregistration,
                                           this);
    connect(watcher, &QDBusServiceWatcher::serviceUnregistered, this, [=] {
        if (d->inited) {
            auto it = d->objects.begin();
            while (it != d->objects.end()) {
                UDisksObject::Ptr object = it.value();
                if (object) {
                    Q_EMIT objectRemoved(object);
                }
                d->objects.erase(it);
            }

            d->inited = false;
            Q_EMIT initChanged();
        }
    });
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

    if (async) {
        QDBusPendingReply<UDManagedObjects> reply = d->objectInterface.GetManagedObjects();
        auto watcher = new QDBusPendingCallWatcher(reply, this);
        connect(watcher, &QDBusPendingCallWatcher::finished, this, [=] {
            QDBusPendingReply<UDManagedObjects> reply = *watcher;
            if (reply.isError()) {
                qCWarning(UDISKSQT_CLIENT) << "Failed to get objects" << reply.error().message();
            } else {
                d->initObjects(reply.value(), this);
            }
            watcher->deleteLater();

            d->inited = true;
            Q_EMIT initChanged();
            Q_EMIT objectsAvailable();
        });
    } else {
        QDBusReply<UDManagedObjects> reply = d->objectInterface.GetManagedObjects();
        d->inited = true;
        Q_EMIT initChanged();

        if (!reply.isValid()) {
            qCWarning(UDISKSQT_CLIENT) << "Failed to get managed objects:" << reply.error().message();
            return false;
        }

        d->initObjects(reply.value(), this);
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
                ret.append(it.value());
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
    for (const QDBusObjectPath &objectPath : objectPaths) {
        UDisksObject::Ptr object = d->objects.value(objectPath);
        if (object) {
            ret.append(object);
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
    const UDisksObject::List blockDevices = getObjects(UDisksObject::BlockDevice);
    for (const UDisksObject::Ptr &object : blockDevices) {
        if (object->partition() && object->partition()->table() == tablePath) {
            ret.append(object);
        }
    }
    return ret;
}

UDisksManager *UDisksClient::manager() const
{
    UDisksManager *ret = nullptr;
    const UDisksObject::List managers = getObjects(UDisksObject::Manager);
    if (!managers.isEmpty()) {
        ret = managers.first()->manager();
    }
    return ret;
}

UDisksClientPrivate::UDisksClientPrivate()
    : objectInterface(QLatin1String(UD2_SERVICE),
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

void UDisksClientPrivate::initObjects(const UDManagedObjects &managedObjects, UDisksClient *client)
{
    UDManagedObjects::ConstIterator it = managedObjects.constBegin();
    while (it != managedObjects.constEnd()) {
        UDisksObject::Ptr object(new UDisksObject(it.key(), it.value(), client));
        objects.insert(it.key(), object);
        ++it;
    }
}

#include "moc_udisksclient.cpp"
