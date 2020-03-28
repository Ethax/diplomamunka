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
    BasicPortTests.h \
    BorisControllerTests.h \
    PropertyHelperTests.h

SOURCES += \
    BasicPortTests.cpp \
    BorisControllerTests.cpp \
    CyclicTimerTests.cpp \
    PropertyHelperTests.cpp \
    TestRunner.cpp

LIBS += \
    -L../../src -lBorisAccess \
    -L../framework -lGoogleTest
