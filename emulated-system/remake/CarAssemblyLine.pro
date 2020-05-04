VERSION = 0.0.1

CONFIG += c++17
QT += quick serialport

INCLUDEPATH += \
    ../../fake-boris/include
    include

SOURCES += src/Main.cpp
RESOURCES += qml/Resources.qrc

TRANSLATIONS += \
    qml/CarAssemblyLine_en_US.ts

CONFIG(release, debug|release): LIBS += -Llibs/BorisAccess/release/ -lBorisAccess
CONFIG(debug, debug|release): LIBS += -Llibs/BorisAccess/debug/ -lBorisAccess
