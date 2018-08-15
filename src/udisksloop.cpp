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

#include "udisksloop.h"
#include "udisksloop_p.h"

#include "common.h"

#include <QDebug>

UDisksLoop::UDisksLoop(const QDBusObjectPath &objectPath, const QVariantMap &properties, UDisksObject *parent) :
    UDisksInterface(parent),
    d_ptr(new UDisksLoopPrivate(objectPath.path()))
{
    Q_D(UDisksLoop);

    d->properties = properties;
}

UDisksLoop::~UDisksLoop()
{
    delete d_ptr;
}

bool UDisksLoop::autoclear() const
{
    Q_D(const UDisksLoop);
    return d->properties.value(QStringLiteral("Autoclear")).toBool();
}

QByteArray UDisksLoop::backingFile() const
{
    Q_D(const UDisksLoop);
    return d->properties.value(QStringLiteral("BackingFile")).toByteArray();
}

uint UDisksLoop::setupByUID() const
{
    Q_D(const UDisksLoop);
    return d->properties.value(QStringLiteral("SetupByUID")).toUInt();
}

QDBusPendingReply<> UDisksLoop::deleteLoop(const QVariantMap &options)
{
    Q_D(UDisksLoop);
    return d->interface.Delete(options);
}

QDBusPendingReply<> UDisksLoop::setAutoclear(bool value, const QVariantMap &options)
{
    Q_D(UDisksLoop);
    return d->interface.SetAutoclear(value, options);
}

void UDisksLoop::propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties)
{
    Q_D(UDisksLoop);
    changeProperties(d->properties, properties, invalidProperties);
}

UDisksLoopPrivate::UDisksLoopPrivate(const QString &path) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus())
{
}
