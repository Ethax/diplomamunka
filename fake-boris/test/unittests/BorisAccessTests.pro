VERSION = 0.0.1

TEMPLATE = app
CONFIG += c++17 console warn_on testcase
CONFIG -= app_bundle debug_and_release
QT += testlib serialport
QT -= gui

INCLUDEPATH += \
    ../../include \
    ../framework/include

HEADERS += \
    BorisControllerTests.h \
    DeveloperPortTests.h \
    PropertyHelperTests.h

SOURCES += \
    BorisControllerTests.cpp \
    CyclicTimerTests.cpp \
    DeveloperPortTests.cpp \
    EchoPortTests.cpp \
    PropertyHelperTests.cpp \
    TestRunner.cpp

LIBS += \
    -L../../src -lBorisAccess \
    -L../framework -lGoogleTest
