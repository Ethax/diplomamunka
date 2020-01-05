QT += core
TEMPLATE = lib
CONFIG += c++17	staticlib

INCLUDEPATH += $$PWD/../include

HEADERS += \
    $$PWD/../include/BorisController.h \
    $$PWD/../include/IOPort.hpp \
    $$PWD/../include/PropertyHelper.hpp \
    $$PWD/../include/Timer.hpp

SOURCES += \
    BorisController.cpp

