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

#include "dbus-types.h"

class UDisksPartitionPrivate;
class UDisksPartition : public QObject
{
    Q_OBJECT
public:
    explicit UDisksPartition(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties, QObject *parent = 0);

    Q_PROPERTY(qulonglong Flags READ flags)
    qulonglong flags() const;

    Q_PROPERTY(bool IsContained READ isContained)
    bool isContained() const;

    Q_PROPERTY(bool IsContainer READ isContainer)
    bool isContainer() const;

    Q_PROPERTY(QString Name READ name)
    QString name() const;

    Q_PROPERTY(uint Number READ number)
    uint number() const;

    Q_PROPERTY(qulonglong Offset READ offset)
    qulonglong offset() const;

    Q_PROPERTY(qulonglong Size READ size)
    qulonglong size() const;

    Q_PROPERTY(QDBusObjectPath Table READ table)
    QDBusObjectPath table() const;

    Q_PROPERTY(QString Type READ type)
    QString type() const;

    Q_PROPERTY(QString UUID READ uUID)
    QString uUID() const;

protected:
    UDisksPartitionPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksPartition)
};

#endif // UDISKSPARTITION_H
