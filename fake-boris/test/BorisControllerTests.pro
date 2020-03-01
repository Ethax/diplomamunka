QT += testlib
QT -= gui

TEMPLATE = app

CONFIG += c++17 qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

INCLUDEPATH += $$PWD/../include

HEADERS += \
    TestDummy.h

SOURCES += \
    TestDummy.cpp \
    BorisControllerTests.cpp

unix|win32: \
    LIBS += -L$$OUT_PWD/../src/ -lBorisAccess

win32:!win32-g++: \
    PRE_TARGETDEPS += $$OUT_PWD/../src/BorisAccess.lib
else:unix|win32-g++: \
    PRE_TARGETDEPS += $$OUT_PWD/../src/libBorisAccess.a
