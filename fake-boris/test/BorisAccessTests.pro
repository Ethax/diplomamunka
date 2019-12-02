QT += testlib
QT -= gui

TEMPLATE = app

CONFIG += c++17 qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/release/ -lBorisAccess
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug/ -lBorisAccess
else:unix: LIBS += -L$$OUT_PWD/../src/ -lBorisAccess

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/release/libBorisAccess.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/debug/libBorisAccess.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/release/BorisAccess.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/debug/BorisAccess.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/libBorisAccess.a

SOURCES += boris_controller_tests.cpp
