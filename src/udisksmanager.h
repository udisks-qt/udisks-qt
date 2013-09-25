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

#ifndef UDISKS_MANAGER_H
#define UDISKS_MANAGER_H

#include <QtCore/QObject>
#include <QtDBus/QDBusObjectPath>
#include <QtDBus/QDBusPendingReply>

#include "udisksinterface.h"
#include "dbus-types.h"

class UDisksManagerPrivate;
class UDisksManager : public UDisksInterface
{
    Q_OBJECT
    Q_PROPERTY(QString version READ version NOTIFY versionChanged)
public:
    explicit UDisksManager(const QDBusObjectPath &objectPath, const QVariantMap &properties, QObject *parent = 0);
    ~UDisksManager();

    /**
     * The daemon version
     */
    Q_PROPERTY(QString version READ version)
    QString version() const;

    /**
     * Creates a block device for the file represented by \p fd.
     *
     * Returns a Block::Ptr
     */
    QDBusPendingReply<QDBusObjectPath> loopSetup(const QDBusUnixFileDescriptor &fd, const QVariantMap &options = QVariantMap());

    /**
     * Creates a new RAID array on the block devices specified by
     * @blocks. Each element in this array must be an object path to
     * an object implementing the #org.freedesktop.UDisks2.Block
     * interface.
     *
     * \p blocks: An array of object paths to objects implementing the #org.freedesktop.UDisks2.Block interface.
     * \p level: The RAID level for the array.
     * \p name: The name for the array.
     * \p chunk: The chunk size (in bytes) or 0 if @level is <quote>raid1</quote>.
     * \p options: Options (currently unused except for <link linkend="udisks-std-options">standard options</link>).
     * returns an MDRaid object
     */
    QDBusPendingReply<QDBusObjectPath> mDRaidCreate(const QList<QDBusObjectPath> &blocks, const QString &level, const QString &name, qulonglong chunk, const QVariantMap &options = QVariantMap());

Q_SIGNALS:
    /**
     * This signal is emitted when a version of the daemon changes.
     */
    void versionChanged();

protected:
    virtual void propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties);
    UDisksManagerPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksManager)
};

#endif // UDISKS_MANAGER_H
