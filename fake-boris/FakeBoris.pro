TEMPLATE = subdirs

SUBDIRS = \
    BorisAccess \
    BorisAccessTests

BorisAccess.file = src/BorisAccess.pro

BorisAccessTests.file = test/BorisAccessTests.pro
BorisAccessTests.depends = BorisAccess
