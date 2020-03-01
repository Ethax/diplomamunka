TEMPLATE = subdirs

SUBDIRS += \
    GoogleTest \
    BorisAccessTests

GoogleTest.file = GoogleTest.pro

BorisAccessTests.file = BorisAccessTests.pro
BorisAccessTests.depends = GoogleTest
