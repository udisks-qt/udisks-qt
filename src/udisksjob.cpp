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

#include "udisksjob.h"
#include "udisksjob_p.h"

#include "common.h"

#include <QDebug>

UDisksJob::UDisksJob(const QDBusObjectPath &objectPath, const QVariantMap &properties, QObject *parent) :
    UDisksInterface(parent),
    d_ptr(new UDisksJobPrivate(objectPath.path()))
{
    Q_D(UDisksJob);

    d->properties = properties;
}

UDisksJob::~UDisksJob()
{
    delete d_ptr;
}

qulonglong UDisksJob::bytes() const
{
    Q_D(const UDisksJob);
    return d->properties[QLatin1String("Bytes")].toULongLong();
}

bool UDisksJob::cancelable() const
{
    Q_D(const UDisksJob);
    return d->properties[QLatin1String("Cancelable")].toBool();
}

qulonglong UDisksJob::expectedEndTime() const
{
    Q_D(const UDisksJob);
    return d->properties[QLatin1String("ExpectedEndTime")].toULongLong();
}

QList<QDBusObjectPath> UDisksJob::objects() const
{
    Q_D(const UDisksJob);
    return d->properties[QLatin1String("Objects")].value<QList<QDBusObjectPath> >();
}

QString UDisksJob::operation() const
{
    Q_D(const UDisksJob);
    return d->properties[QLatin1String("Operation")].toString();
}

double UDisksJob::progress() const
{
    Q_D(const UDisksJob);
    return d->properties[QLatin1String("Progress")].toDouble();
}

bool UDisksJob::progressValid() const
{
    Q_D(const UDisksJob);
    return d->properties[QLatin1String("ProgressValid")].toBool();
}

qulonglong UDisksJob::rate() const
{
    Q_D(const UDisksJob);
    return d->properties[QLatin1String("Rate")].toULongLong();
}

qulonglong UDisksJob::startTime() const
{
    Q_D(const UDisksJob);
    return d->properties[QLatin1String("StartTime")].toULongLong();
}

uint UDisksJob::startedByUID() const
{
    Q_D(const UDisksJob);
    return d->properties[QLatin1String("StartedByUID")].toUInt();
}

QDBusPendingReply<> UDisksJob::cancel(const QVariantMap &options)
{
    Q_D(UDisksJob);
    return d->interface.Cancel(options);
}

void UDisksJob::propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties)
{
    Q_D(UDisksJob);
    changeProperties(d->properties, properties, invalidProperties);
}

UDisksJobPrivate::UDisksJobPrivate(const QString &path) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus())
{
}
