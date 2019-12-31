QT += core
TEMPLATE = lib
CONFIG += c++17	staticlib

INCLUDEPATH += ../include

HEADERS += \
    ../include/AbstractBorisController.h \
    ../include/PropertyHelper.hpp

SOURCES += \
    AbstractBorisController.cpp

