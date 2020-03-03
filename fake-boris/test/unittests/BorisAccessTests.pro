QT += testlib
QT -= gui

TEMPLATE = app

CONFIG += c++17 console warn_on testcase
CONFIG -= app_bundle debug_and_release

INCLUDEPATH += \
    ../../include \
    ../framework/include

SOURCES += \
    BorisAccessTestRunner.cpp \
    BorisControllerTests.cpp \
    PropertyHelperTests.cpp

LIBS += \
    -L../../src -lBorisAccess \
    -L../framework -lGoogleTest
