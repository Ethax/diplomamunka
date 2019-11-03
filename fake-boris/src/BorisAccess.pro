QT += core
TEMPLATE = lib
CONFIG += c++17 staticlib

INCLUDEPATH += $$PWD/../include

HEADERS += \
    $$PWD/../include/boris_controller.h \
    $$PWD/../include/connection_provider.h

SOURCES += boris_controller.cpp

