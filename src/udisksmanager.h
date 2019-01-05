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
    explicit UDisksManager(const QDBusObjectPath &objectPath, const QVariantMap &properties, UDisksObject *parent = nullptr);
    ~UDisksManager();

    /**
     * The version of the daemon currently running
     */
    QString version() const;

    /**
     * List of supported filesystem by UDisks2
     */
    QStringList supportedFilesystems() const;

    /**
     * @brief canCheck Checking availability and the required binary name if missing (i.e. no error and returns FALSE).
     * @param type The filesystem type to be tested for consistency check availability.
     * @since: 2.7.2
     *
     * Tests for availability to check the given filesystem.
     * Unsupported filesystems or filesystems which do not support checking result in errors.
     */
    QDBusPendingReply<UDisksTypeAvailable> canCheck(const QString &type);

    /**
     * @param type The filesystem type to be tested for formatting availability.
     * @brief Tests for availability to create the given filesystem.
     * See the #org.freedesktop.UDisks2.Manager:SupportedFilesystems property
     * for a list of known types. Unknown or unsupported filesystems result in an error.
     */
    QDBusPendingReply<UDisksTypeAvailable> canFormat(const QString &type);

    /**
     * @param type The filesystem type to be tested for repair availability.
     * @brief Repair availability and the required binary name if missing (i.e. no error and returns FALSE).
     * @since: 2.7.2
     *
     * Tests for availability repair the given filesystem.
     * Unsupported filesystems or filesystems which do not support repairing result in errors.
     */
    QDBusPendingReply<UDisksTypeAvailable> canRepair(const QString &type);

    /**
     * @param type The filesystem type to be tested for resize availability.
     * @brief Resizing availability, flags for allowed resizing (i.e. growing/shrinking support for online/offline)
     * and the required binary name if missing (i.e. no error and returns FALSE).
     * @since: 2.7.2
     *
     * Tests for availability to resize the given filesystem.
     * The mode flags indicate if growing and/or shriking resize is available if mounted/unmounted.
     * The mode corresponds to bitwise-OR combined BDFsResizeFlags of the libblockdev FS plugin:
     * BD_FS_OFFLINE_SHRINK = 2, shrinking resize allowed when unmounted
     * BD_FS_OFFLINE_GROW = 4, growing resize allowed when unmounted
     * BD_FS_ONLINE_SHRINK = 8, shrinking resize allowed when mounted
     * BD_FS_ONLINE_GROW = 16, growing resize allowed when mounted
     * Unknown filesystems or filesystems which do not support resizing result in errors.
     */
    QDBusPendingReply<UDisksTypeAvailableFlags> canResize(const QString &type);

    /**
     * @param enable A boolean value indicating whether modules should be enabled. Currently only the TRUE value is permitted.
     *
     * Loads and activates modules. This action also causes all objects to receive "add" uevent that triggers additional module interfaces activation.
     *
     * Modules cannot be deactivated for the moment. Any consecutive calls with modules already enabled equals to noop.
     */
    QDBusPendingReply<> enableModules(bool enable);

    /**
     * @param options Options (currently unused except for <link linkend="udisks-std-options">standard options</link>).
     * @since: 2.7.2
     *
     * Get list of all block devices (object paths of objects implementing the #org.freedesktop.UDisks2.Block interface) known to UDisks.
     */
    QDBusPendingReply<QList<QDBusObjectPath> > getBlockDevices(const QVariantMap &options);

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

    /**
     * @param devspec Dictionary with specification of a device.
     * @param options Options (currently unused except for <link linkend="udisks-std-options">standard options</link>).
     * @return List of object paths of all devices matching @devspec.
     * @since: 2.7.3
     *
     * Get device(s) matching specification given in @devspec.
     *
     * Currently supported keys for @devspec include:
     * <variablelist>
     *   <varlistentry>
     *     <term>path (type <literal>'s'</literal>)</term>
     *     <listitem><para>
     *       Device path (e.g. <quote>/dev/sda</quote>). This also includes symlinks in <quote>/dev</quote>
     *       (both #org.freedesktop.UDisks2.Block:Device and #org.freedesktop.UDisks2.Block:Symlinks are used).
     *     </para></listitem>
     *   </varlistentry>
     *   <varlistentry>
     *     <term>label (type <literal>'s'</literal>)</term>
     *     <listitem><para>
     *       Filesystem label. #org.freedesktop.UDisks2.Block:IdLabel is used.
     *     </para></listitem>
     *   </varlistentry>
     *   <varlistentry>
     *     <term>uuid (type <literal>'s'</literal>)</term>
     *     <listitem><para>
     *       Filesystem UUID. #org.freedesktop.UDisks2.Block:IdUUID is used.
     *     </para></listitem>
     *   </varlistentry>
     * </variablelist>
     *
     * It is possbile to specify multiple keys. In this case, only devices matching all values will be returned.
     */
    QDBusPendingReply<QList<QDBusObjectPath> > resolveDevice(const QVariantMap &devspec, const QVariantMap &options);

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
