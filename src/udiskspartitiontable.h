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

#ifndef UDISKSPARTITIONTABLE_H
#define UDISKSPARTITIONTABLE_H

#include <QObject>
#include <QtDBus/QDBusPendingReply>

#include "udisksinterface.h"
#include "dbus-types.h"

class UDisksPartitionTablePrivate;
class UDisksPartitionTable : public UDisksInterface
{
    Q_OBJECT
public:
    typedef QSharedPointer<UDisksPartitionTable> Ptr;
    typedef QList<Ptr> List;
    explicit UDisksPartitionTable(const QDBusObjectPath &objectPath, const QVariantMap &properties, QObject *parent = 0);
    ~UDisksPartitionTable();

    Q_PROPERTY(QString type READ type)
    QString type() const;

public Q_SLOTS:
    QDBusPendingReply<QDBusObjectPath> createPartition(qulonglong offset, qulonglong size, const QString &type, const QString &name, const QVariantMap &options);

protected:
    virtual void propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties);
    UDisksPartitionTablePrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksPartitionTable)
};

#endif // UDISKSPARTITIONTABLE_H
