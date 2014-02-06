cmake_minimum_required(VERSION 2.6)

pkg_check_modules(GTK3 REQUIRED
  gtk+-3.0
  gmodule-2.0
)

set(GTK3_ABI_VERSION)
# this is a private macro of FindPkgConfig
# _pkgconfig_invoke("gtk+-3.0" GTK3_ABI_VERSION "" "--variable=gtk_binary_version")
execute_process(
  COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=gtk_binary_version gtk+-3.0
  OUTPUT_VARIABLE GTK3_ABI_VERSION
)
string(STRIP ${GTK3_ABI_VERSION} GTK3_ABI_VERSION)

include_directories(
  ${QT_INCLUDES}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${GTK3_INCLUDE_DIRS}
)

set(qt-gtk-engine_SRCS
  # themeengine.cpp
  themepainter.cpp
  cssprovider.cpp
  main.cpp
)

qt4_automoc(${qt-gtk-engine_SRCS})

add_library(qt-gtk-engine MODULE ${qt-gtk-engine_SRCS})
# set_target_properties(qt-gtk-engine PROPERTIES PREFIX "")

target_link_libraries(qt-gtk-engine
  ${QT_QTCORE_LIBRARY}
  ${QT_QTGUI_LIBRARY}
  ${GTK3_LIBRARIES}
  -Wl,-no-undefined
)

install(TARGETS qt-gtk-engine DESTINATION lib/gtk-3.0/${GTK3_ABI_VERSION}/theming-engines)
install(FILES settings.ini gtk.css DESTINATION share/themes/qt-gtk-engine/gtk-3.0)
