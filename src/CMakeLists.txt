# CMakeLists for UDisks-Qt library
set(CMAKE_AUTOMOC ON)

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Core_DEFINITIONS})
add_definitions(-fPIC)

include_directories(${CMAKE_BINARY_DIR}
		    ${CMAKE_CURRENT_BINARY_DIR}
		    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(udisksqt_SRC
    dbus-types.cpp
    udisksblock.cpp
    udisksdrive.cpp
    udisksdriveata.cpp
    udisksmdraid.cpp
    udisksjob.cpp
    udiskspartition.cpp
    udiskspartitiontable.cpp
    udisksfilesystem.cpp
    udisksobject.cpp
    udisksmanagerprivate.cpp
    udisksmanager.cpp
)

set(udisksqt_HEADERS
    udisksblock.h
    UDisksBlock
    udisksdrive.h
    UDisksDrive
    udisksdriveata.h
    UDisksDriveAta
    udisksmdraid.h
    UDisksMDRaid
    udisksjob.h
    UDisksJob
    udiskspartition.h
    UDisksPartition
    udiskspartitiontable.h
    UDisksPartitionTable
    udisksfilesystem.h
    UDisksFilesystem
    udisksobject.h
    UDisksObject
    udisksmanager.h
    UDisksManager
)

set(udisksqt_HEADERS_PRIVATE
    dbus-types.h
    common.h
    udisksblock_p.h
    udisksdrive_p.h
    udisksdriveata_p.h
    udisksmdraid_p.h
    udisksjob_p.h
    udiskspartition_p.h
    udiskspartitiontable_p.h
    udisksfilesystem_p.h
    udisksobject_p.h
    udisksmanagerprivate.h
)

set_property(SOURCE org.freedesktop.UDisks2.xml PROPERTY INCLUDE dbus-types.h)
set_property(SOURCE org.freedesktop.UDisks2.xml PROPERTY NO_NAMESPACE true)
qt5_add_dbus_interface(udisksqt_SRC org.freedesktop.UDisks2.xml UDisks)

set_property(SOURCE org.freedesktop.DBus.ObjectManager.xml PROPERTY INCLUDE dbus-types.h)
set_property(SOURCE org.freedesktop.DBus.ObjectManager.xml PROPERTY NO_NAMESPACE true)
qt5_add_dbus_interface(udisksqt_SRC org.freedesktop.DBus.ObjectManager.xml DBusObjectManager)

qt5_wrap_cpp(udisksqt_MOC_SRC ${udisksqt_HEADERS} ${udisksqt_HEADERS_PRIVATE})

add_library(udisks2-qt5 SHARED ${udisksqt_SRC} ${udisksqt_HEADERS} ${udisksqt_HEADERS_PRIVATE})
set_target_properties(udisks2-qt5 PROPERTIES VERSION ${UDISKS_VERSION} SOVERSION ${UDISKS_API_LEVEL})

target_link_libraries(udisks2-qt5
    ${Qt5Core_LIBRARIES}
    ${Qt5DBus_LIBRARIES}
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/udisks-qt5.pc.in
  ${CMAKE_CURRENT_BINARY_DIR}/udisks-qt5.pc
  @ONLY
)

install(TARGETS udisks2-qt5 DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/udisks-qt5.pc
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
install(FILES ${udisksqt_HEADERS}
        DESTINATION include/UDisks2Qt5/UDisks
)

add_subdirectory(modules)
