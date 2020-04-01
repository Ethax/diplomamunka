TEMPLATE = subdirs

SUBDIRS = \
    BorisAccess \
    TestSuite \
    BorisUI

BorisAccess.file = src/BorisAccess.pro

TestSuite.file = test/TestSuite.pro
TestSuite.depends = BorisAccess

BorisUI.file = qml/BorisUI.pro
BorisUI.depends = BorisAccess