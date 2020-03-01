QT += core
TEMPLATE = lib
CONFIG += c++17	staticlib

INCLUDEPATH += $$PWD/../include

HEADERS += \
    $$PWD/../include/BorisController.h \
    $$PWD/../include/IOPort.hpp \
    $$PWD/../include/PropertyHelper.hpp \
    $$PWD/../include/Timer.hpp \
    $$PWD/../include/Exception.h \
    $$PWD/../include/Verify.hpp

SOURCES += \
    BorisController.cpp \
    Exception.cpp
