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

#ifndef UDISKSPARTITION_H
#define UDISKSPARTITION_H

#include <QObject>
#include <QtDBus/QDBusPendingReply>

#include "udisksinterface.h"
#include "dbus-types.h"

class UDisksPartitionPrivate;
class UDisksPartition : public UDisksInterface
{
    Q_OBJECT
public:
    typedef QSharedPointer<UDisksPartition> Ptr;
    typedef QList<Ptr> List;
    explicit UDisksPartition(const QDBusObjectPath &objectPath, const QVariantMap &properties, QObject *parent = 0);
    ~UDisksPartition();

    Q_PROPERTY(qulonglong flags READ flags)
    qulonglong flags() const;

    Q_PROPERTY(bool isContained READ isContained)
    bool isContained() const;

    Q_PROPERTY(bool isContainer READ isContainer)
    bool isContainer() const;

    Q_PROPERTY(QString name READ name)
    QString name() const;

    Q_PROPERTY(uint number READ number)
    uint number() const;

    Q_PROPERTY(qulonglong offset READ offset)
    qulonglong offset() const;

    Q_PROPERTY(qulonglong size READ size)
    qulonglong size() const;

    Q_PROPERTY(QDBusObjectPath table READ table)
    QDBusObjectPath table() const;

    Q_PROPERTY(QString type READ type)
    QString type() const;

    Q_PROPERTY(QString uUID READ uUID)
    QString uUID() const;

public Q_SLOTS:
    QDBusPendingReply<> deletePartition(const QVariantMap &options);

    QDBusPendingReply<> setFlags(qulonglong flags, const QVariantMap &options);

    QDBusPendingReply<> setName(const QString &name, const QVariantMap &options);

    QDBusPendingReply<> setType(const QString &type, const QVariantMap &options);

protected:
    virtual void propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties);
    UDisksPartitionPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksPartition)
};

#endif // UDISKSPARTITION_H
