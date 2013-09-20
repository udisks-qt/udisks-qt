# CMakeLists for libudisks-qt
project(udisks-qt)

cmake_minimum_required(VERSION 2.8.6 FATAL_ERROR)
find_package(PkgConfig REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5DBus REQUIRED)

set(CMAKE_BUILD_TYPE "Debug")

set(UDISKS_VERSION_MAJOR  "0")
set(UDISKS_VERSION_MINOR  "0")
set(UDISKS_VERSION_PATCH  "0")
set(UDISKS_VERSION_SUFFIX "${VERSION_SUFFIX}")
set(UDISKS_VERSION "${UDISKS_VERSION_MAJOR}.${UDISKS_VERSION_MINOR}.${UDISKS_VERSION_PATCH}")

set(UDISKS_API_LEVEL "0")

# Forbid in-tree building
if(${CMAKE_SOURCE_DIR} MATCHES ${CMAKE_BINARY_DIR})
      message(STATUS "Please do an out-of-tree build:")
      message(STATUS "rm -f CMakeCache.txt && mkdir build && cd build; cmake .. && make")
      message(FATAL_ERROR "In-tree-build detected!")
endif(${CMAKE_SOURCE_DIR} MATCHES ${CMAKE_BINARY_DIR})

#
# Options
#

# NONE

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX
    "/usr" CACHE PATH "udisks default install prefix" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

#
# Configure files
#
set (PREFIXDIR "${CMAKE_INSTALL_PREFIX}")
set (DATADIR "${CMAKE_INSTALL_PREFIX}/share")
set (PKGDATADIR "${DATA_INSTALL_DIR}")
set (LIBDIR "${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}")
set (PKGLIBDIR "${LIBDIR}/udisks")
set (GETTEXT_PACKAGE "udisks")
set (LOCALE_DIR "${DATADIR}/locale")
set (VERSION "${UDISKS_VERSION}")
set (BUILDDIR "${CMAKE_BINARY_DIR}")
set (LOCALSTATEDIR "/var")

add_definitions("-DLOCALSTATEDIR=\"${LOCALSTATEDIR}\"")

set(CMAKE_INSTALL_LIBDIR "lib/${CMAKE_LIBRARY_ARCHITECTURE}" CACHE PATH "Output directory for libraries")

configure_file(config.h.in ${CMAKE_BINARY_DIR}/config.h)

#
# Custom C flags
#
set (MAINTAINER_CFLAGS "-Werror -Wall -Wcast-align -Wno-uninitialized -Wempty-body -Wformat-security -Winit-self")
option (DISABLE_MAINTAINER_CFLAGS "Disable maintainer CFlags" ON)
if (DISABLE_MAINTAINER_CFLAGS)
	set (MAINTAINER_CFLAGS "")
endif (DISABLE_MAINTAINER_CFLAGS)
add_definitions(${MAINTAINER_CFLAGS})

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Qt5Core_INCLUDE_DIRS}
)

add_subdirectory(src)
