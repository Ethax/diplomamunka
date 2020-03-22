VERSION = 0.0.1

TEMPLATE = app
CONFIG += c++17 console warn_on testcase
CONFIG -= app_bundle debug_and_release
QT += testlib serialport concurrent
QT -= gui

INCLUDEPATH += \
    ../../include \
    ../framework/include

HEADERS += \
    BorisControllerTests.h \
    PropertyHelperTests.h

SOURCES += \
    ../framework/src/gmock/src/gmock_main.cc \
    BorisControllerTests.cpp \
    CyclicTimerTests.cpp \
    PropertyHelperTests.cpp

LIBS += \
    -L../../src -lBorisAccess \
    -L../framework -lGoogleTest
