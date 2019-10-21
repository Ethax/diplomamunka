QT += testlib
QT -= gui

TEMPLATE = app

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/release/ -lFakeBorisLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug/ -lFakeBorisLib
else:unix: LIBS += -L$$OUT_PWD/../src/ -lFakeBorisLib

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/release/libFakeBorisLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/debug/libFakeBorisLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/release/FakeBorisLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/debug/FakeBorisLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/libFakeBorisLib.a

SOURCES += tst_fakeboristests.cpp
