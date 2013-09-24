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

#ifndef UDISKSFILESYSTEM_H
#define UDISKSFILESYSTEM_H

#include <QObject>
#include <QtDBus/QDBusPendingReply>

#include "dbus-types.h"

class UDisksFilesystemPrivate;
class UDisksFilesystem : public QObject
{
    Q_OBJECT
public:
    typedef QSharedPointer<UDisksFilesystem> Ptr;
    typedef QList<Ptr> List;
    explicit UDisksFilesystem(const QDBusObjectPath &objectPath, const QVariantMap &properties, QObject *parent = 0);
    ~UDisksFilesystem();

    Q_PROPERTY(QList<QByteArray> mountPoints READ mountPoints)
    QList<QByteArray> mountPoints() const;

public Q_SLOTS:
    QDBusPendingReply<QString> mount(const QVariantMap &options);

    QDBusPendingReply<> setLabel(const QString &label, const QVariantMap &options);

    QDBusPendingReply<> unmount(const QVariantMap &options);

protected:
    UDisksFilesystemPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksFilesystem)
};

#endif // UDISKSFILESYSTEM_H
