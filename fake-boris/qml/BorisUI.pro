VERSION = 0.0.1

CONFIG += c++17
QT += quick serialport

INCLUDEPATH += ../include

SOURCES += Main.cpp
RESOURCES += Resources.qrc
RC_ICONS = ApplicationIcon.ico
LIBS += -L../src -lBorisAccess

TRANSLATIONS += \
    BorisUI_en_US.ts

