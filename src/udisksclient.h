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

#ifndef UDISKSCLIENT_H
#define UDISKSCLIENT_H

#include <QObject>

#include "udisksdefs.h"
#include "udisksobject.h"

class UDisksClientPrivate;
class UDISKS_EXPORT UDisksClient : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief UDisksClient Creates the main UDisks class
     * This class must be initted so that it's functions
     * become populated.
     * @param parent
     */
    explicit UDisksClient(QObject *parent = 0);
    ~UDisksClient();

    Q_PROPERTY(bool inited READ inited)
    bool inited() const;

    /**
     * As UDisks daemon is DBus-Activated which means
     * it might not be running at the time this class is
     * created, so it's recommended that you init it
     * async to not block user interface untill we
     * have all data.
     */
    bool init(bool async = true);

    UDisksObject::List getObjects(UDisksObject::Kind kind = UDisksObject::Any) const;

    UDisksObject::List getObjects(const QList<QDBusObjectPath> &objectPaths) const;

    UDisksObject::Ptr getObject(const QDBusObjectPath &objectPath) const;

    UDisksManager *manager() const;

Q_SIGNALS:
    void objectsAvailable();
    void objectAdded(const UDisksObject::Ptr &object);
    void objectRemoved(const UDisksObject::Ptr &object);
    void interfacesAdded(const UDisksObject::Ptr &object);
    void interfacesRemoved(const UDisksObject::Ptr &object);

protected:
    UDisksClientPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksClient)
    Q_PRIVATE_SLOT(d_func(), void _q_interfacesAdded(const QDBusObjectPath &, UDVariantMapMap))
    Q_PRIVATE_SLOT(d_func(), void _q_interfacesRemoved(const QDBusObjectPath &, const QStringList &))
    Q_PRIVATE_SLOT(d_func(), void _q_getObjectsFinished(QDBusPendingCallWatcher *))
};

#endif // UDISKSCLIENT_H
