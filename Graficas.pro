CONFIG      += designer plugin debug_and_release
TARGET      = $$qtLibraryTarget(graficaplugin)
TEMPLATE    = lib

HEADERS     = graficaplugin.h
SOURCES     = graficaplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(grafica.pri)
