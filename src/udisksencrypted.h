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

#ifndef UDISKSENCRYPTED_H
#define UDISKSENCRYPTED_H

#include <QObject>
#include <QtDBus/QDBusPendingReply>

#include "udisksinterface.h"
#include "dbus-types.h"

class UDisksEncryptedPrivate;
class UDisksEncrypted : public UDisksInterface
{
    Q_OBJECT
public:
    explicit UDisksEncrypted(const QDBusObjectPath &objectPath, const QVariantMap &properties, QObject *parent = 0);
    ~UDisksEncrypted();

public Q_SLOTS:
    QDBusPendingReply<> changePassphrase(const QString &passphrase, const QString &newPassphrase, const QVariantMap &options = QVariantMap());

    QDBusPendingReply<> lock(const QVariantMap &options = QVariantMap());

    QDBusPendingReply<QDBusObjectPath> unlock(const QString &passphrase, const QVariantMap &options = QVariantMap());

protected:
    virtual void propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties);
    UDisksEncryptedPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksEncrypted)
};

#endif // UDISKSENCRYPTED_H
