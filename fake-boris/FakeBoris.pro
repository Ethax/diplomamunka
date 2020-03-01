TEMPLATE = subdirs

SUBDIRS = \
    BorisAccess \
    TestSuite

BorisAccess.file = src/BorisAccess.pro

TestSuite.file = test/TestSuite.pro
TestSuite.depends = BorisAccess
