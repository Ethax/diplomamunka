QT += core
TEMPLATE = lib
CONFIG += c++17	staticlib

INCLUDEPATH += ../include

HEADERS += \
    ../include/BorisController.h \
    ../include/IOPort.hpp \
    ../include/PropertyHelper.hpp \
    ../include/Timer.hpp \
    ../include/Exception.h \
    ../include/Verify.hpp

SOURCES += \
    BorisController.cpp \
    Exception.cpp
