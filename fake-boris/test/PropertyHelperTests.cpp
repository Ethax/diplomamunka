#include <PropertyHelper.hpp>
#include <QCoreApplication>
#include <QMetaProperty>
#include <QSignalSpy>
#include <QtTest>

class PropertyHelperTests : public QObject {
    Q_OBJECT
    AUTOMATIC_PROPERTY(int, AutomaticProperty) = 0;
    READONLY_PROPERTY(int, ReadonlyProperty) = 0;

private slots:
    void init() {
        m_AutomaticProperty = 0;
        m_ReadonlyProperty = 0;
    }

    void AutomaticProperty_Exists_IsReadable() {
        const QMetaProperty property = GetProperty("AutomaticProperty");

        QCOMPARE(property.isReadable(), true);
    }

    void AutomaticProperty_Exists_IsWritable() {
        const QMetaProperty property = GetProperty("AutomaticProperty");

        QCOMPARE(property.isWritable(), true);
    }

    void AutomaticProperty_Exists_HasNotifySignal() {
        const QMetaProperty property = GetProperty("AutomaticProperty");

        QVERIFY(property.hasNotifySignal());
        QCOMPARE(property.notifySignal().name(), "AutomaticPropertyChanged");
    }

    void AutomaticProperty_CommonSetterWasCalled_ChangesItsUnderlyingMember() {
        const bool propertChanged = setProperty("AutomaticProperty", ExpectedValue);

        QCOMPARE(propertChanged, true);
        QCOMPARE(m_AutomaticProperty, ExpectedValue);
    }

    void AutomaticProperty_DedicatedSetterWasCalled_ChangesItsUnderlyingMember() {
        SetAutomaticProperty(ExpectedValue);

        QCOMPARE(m_AutomaticProperty, ExpectedValue);
    }

    void AutomaticProperty_CommonGetterWasCalled_ReturnsItsUnderlyingMember() {
        m_AutomaticProperty = ExpectedValue;

        QCOMPARE(property("AutomaticProperty").toInt(), ExpectedValue);
    }

    void AutomaticProperty_DedicatedGetterWasCalled_ReturnsItsUnderlyingMember() {
        m_AutomaticProperty = ExpectedValue;

        QCOMPARE(GetAutomaticProperty(), ExpectedValue);
    }

    void AutomaticProperty_CommonSetterWasCalledTwiceWithSameValue_NotifiesOnlyOnce() {
        QSignalSpy notification(this, &PropertyHelperTests::AutomaticPropertyChanged);

        setProperty("AutomaticProperty", ExpectedValue);
        setProperty("AutomaticProperty", ExpectedValue);

        QTRY_COMPARE_WITH_TIMEOUT(notification.count(), 1, NotificationTimeout);
    }

    void AutomaticProperty_DedicatedSetterWasCalledTwiceWithSameValue_NotifiesOnlyOnce() {
        QSignalSpy notification(this, &PropertyHelperTests::AutomaticPropertyChanged);

        SetAutomaticProperty(ExpectedValue);
        SetAutomaticProperty(ExpectedValue);

        QTRY_COMPARE_WITH_TIMEOUT(notification.count(), 1, NotificationTimeout);
    }

    //---------------------------------------------------

private:
    static QMetaProperty GetProperty(const char *name) {
        return staticMetaObject.property(staticMetaObject.indexOfProperty(name));
    }

    static constexpr int ExpectedValue = 42;
    static constexpr int NotificationTimeout = 1000;
};

QTEST_MAIN(PropertyHelperTests)

#include "PropertyHelperTests.moc"
