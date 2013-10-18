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

#ifndef UDISKSLOOP_H
#define UDISKSLOOP_H

#include <QObject>
#include <QtDBus/QDBusPendingReply>

#include "udisksinterface.h"
#include "dbus-types.h"

class UDisksLoopPrivate;
class UDisksLoop : public UDisksInterface
{
    Q_OBJECT
public:
    explicit UDisksLoop(const QDBusObjectPath &objectPath, const QVariantMap &properties, UDisksObject *parent = 0);
    ~UDisksLoop();

    Q_PROPERTY(bool autoclear READ autoclear)
    bool autoclear() const;

    Q_PROPERTY(QByteArray backingFile READ backingFile)
    QByteArray backingFile() const;

    Q_PROPERTY(uint setupByUID READ setupByUID)
    uint setupByUID() const;

public Q_SLOTS:
    QDBusPendingReply<> deleteLoop(const QVariantMap &options = QVariantMap());

    QDBusPendingReply<> setAutoclear(bool value, const QVariantMap &options = QVariantMap());

protected:
    virtual void propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties);
    UDisksLoopPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksLoop)
};

#endif // UDISKSLOOP_H
