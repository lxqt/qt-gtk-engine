project(qt-gtk-engines)
cmake_minimum_required(VERSION 2.6)

find_package(Qt4 REQUIRED)

find_package(PkgConfig)

add_subdirectory(gtk3)
