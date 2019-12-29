QT += core
TEMPLATE = lib
CONFIG += c++17	staticlib

INCLUDEPATH += $$PWD/../include

HEADERS += \
    $$PWD/../include/boris_controller.h \
    $$PWD/../include/connection_provider.h \
    $$PWD/../include/abstract_boris_controller.h \
    $$PWD/../include/property_helper.h

SOURCES += boris_controller.cpp \
    abstract_boris_controller.cpp

