VERSION = 1.10.0

TEMPLATE = lib
CONFIG += c++17	staticlib
CONFIG -= debug_and_release

INCLUDEPATH += \
    include \
    src/gmock \
    src/gtest

SOURCES = \
    src/gmock/gmock-all.cc \
    src/gtest/gtest-all.cc
