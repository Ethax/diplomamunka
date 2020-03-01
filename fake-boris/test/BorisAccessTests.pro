QT += testlib
QT -= gui

TEMPLATE = app

CONFIG += c++17 console warn_on depend_includepath testcase
CONFIG -= app_bundle debug_and_release

INCLUDEPATH += \
    $$SOURCE_DIR/include \
    $$THIRD_PARTY_DIR/googletest-release-1.10.0/googletest/include \
    $$THIRD_PARTY_DIR/googletest-release-1.10.0/googlemock/include

SOURCES += \
    BorisAccessTestRunner.cpp \
    BorisControllerTests.cpp \
    PropertyHelperTests.cpp

LIBS += \
    -L$$BINARY_DIR/src/ -lBorisAccess \
    -L$$BINARY_DIR/test/ -lGoogleTest
