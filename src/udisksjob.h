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

#ifndef UDISKSJOB_H
#define UDISKSJOB_H

#include <QObject>
#include <QtDBus/QDBusPendingReply>

#include "udisksinterface.h"
#include "dbus-types.h"

class UDisksJobPrivate;
class UDisksJob : public UDisksInterface
{
    Q_OBJECT
public:
    typedef QSharedPointer<UDisksJob> Ptr;
    typedef QList<Ptr> List;
    explicit UDisksJob(const QDBusObjectPath &objectPath, const QVariantMap &properties, QObject *parent = 0);
    ~UDisksJob();

    Q_PROPERTY(qulonglong bytes READ bytes)
    qulonglong bytes() const;

    Q_PROPERTY(bool cancelable READ cancelable)
    bool cancelable() const;

    Q_PROPERTY(qulonglong expectedEndTime READ expectedEndTime)
    qulonglong expectedEndTime() const;

    Q_PROPERTY(QList<QDBusObjectPath> objects READ objects)
    QList<QDBusObjectPath> objects() const;

    Q_PROPERTY(QString operation READ operation)
    QString operation() const;

    Q_PROPERTY(double progress READ progress)
    double progress() const;

    Q_PROPERTY(bool progressValid READ progressValid)
    bool progressValid() const;

    Q_PROPERTY(qulonglong rate READ rate)
    qulonglong rate() const;

    Q_PROPERTY(qulonglong startTime READ startTime)
    qulonglong startTime() const;

    Q_PROPERTY(uint startedByUID READ startedByUID)
    uint startedByUID() const;

public Q_SLOTS:
    QDBusPendingReply<> cancel(const QVariantMap &options);

protected:
    virtual void propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties);
    UDisksJobPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksJob)
};

#endif // UDISKSJOB_H
