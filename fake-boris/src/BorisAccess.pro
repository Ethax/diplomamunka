VERSION = 0.0.1

TEMPLATE = lib
CONFIG += c++17	staticlib
QT += core serialport

INCLUDEPATH += ../include

HEADERS += \
    ../include/BorisController.h \
    ../include/CyclicTimer.h \
    ../include/DeveloperPort.h \
    ../include/EchoPort.h \
    ../include/IOPort.hpp \
    ../include/PropertyHelper.hpp \
    ../include/SerialPort.h \
    ../include/Timer.hpp \
    ../include/Exception.h \
    ../include/VirtualPort.h

SOURCES += \
    BorisController.cpp \
    CyclicTimer.cpp \
    DeveloperPort.cpp \
    EchoPort.cpp \
    Exception.cpp \
    SerialPort.cpp \
    VirtualPort.cpp
