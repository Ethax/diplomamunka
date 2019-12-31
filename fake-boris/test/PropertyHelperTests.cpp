#include <PropertyHelper.hpp>
#include <QCoreApplication>
#include <QList>
#include <QMetaProperty>
#include <QtTest>
#include <algorithm>

namespace {

class AutomaticPropertyTester final : public QObject {
    Q_OBJECT
    AUTOMATIC_PROPERTY(int, Property) = 0;
};

class ReadonlyPropertyTester final : public QObject {
    Q_OBJECT
    READONLY_PROPERTY(int, Property) = 0;
};

QMetaProperty GetProperty(QObject *object, const char *name) {
    const QMetaObject *metaObject = object ? object->metaObject() : nullptr;
    return metaObject ? metaObject->property(metaObject->indexOfProperty(name)) : QMetaProperty();
}

} // namespace

class PropertyHelperTests : public QObject {
    Q_OBJECT
private slots:
    void initTestCase_data() {
        QTest::addColumn<QObject *>("propertyTester");
        QTest::newRow("Automatic") << static_cast<QObject *>(new AutomaticPropertyTester());
        QTest::newRow("Readonly") << static_cast<QObject *>(new ReadonlyPropertyTester());
    }

    void test_case1() {
        QFETCH_GLOBAL(QObject *, propertyTester);
        const QMetaProperty property = GetProperty(propertyTester, "Property");

        QVERIFY(property.isReadable());
        QVERIFY(property.isWritable());
        QCOMPARE(property.notifySignal().name(), "PropertyChanged");
    }
};

QTEST_MAIN(PropertyHelperTests)

#include "PropertyHelperTests.moc"
