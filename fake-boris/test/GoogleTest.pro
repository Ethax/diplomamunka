TEMPLATE = lib
CONFIG += c++17	staticlib exceptions
CONFIG -= debug_and_release

GOOGLE_TEST_DIR = $$THIRD_PARTY_DIR/googletest-release-1.10.0

INCLUDEPATH += \
    $$GOOGLE_TEST_DIR/googletest/include \
    $$GOOGLE_TEST_DIR/googlemock/include \
    $$GOOGLE_TEST_DIR/googletest \
    $$GOOGLE_TEST_DIR/googlemock

SOURCES = \
    $$GOOGLE_TEST_DIR/googletest/src/gtest-all.cc \
    $$GOOGLE_TEST_DIR/googlemock/src/gmock-all.cc
