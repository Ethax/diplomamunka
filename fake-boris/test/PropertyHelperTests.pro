QT += testlib
QT -= gui

TEMPLATE = app

CONFIG += c++17 qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

INCLUDEPATH += $$PWD/../include

SOURCES += PropertyHelperTests.cpp
