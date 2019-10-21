TEMPLATE = subdirs

SUBDIRS = \
    FakeBorisLib \
    FakeBorisTests

FakeBorisLib.file = src/FakeBorisLib.pro

FakeBorisTests.file = test/FakeBorisTests.pro
FakeBorisTests.depends = FakeBorisLib
