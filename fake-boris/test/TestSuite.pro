TEMPLATE = subdirs

SUBDIRS += \
    GoogleTest \
    BorisAccessTests

GoogleTest.file = framework/GoogleTest.pro

BorisAccessTests.file = unittests/BorisAccessTests.pro
BorisAccessTests.depends = GoogleTest
