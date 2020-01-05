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
        QCOMPARE(property.notifySignal().methodSignature(), "AutomaticPropertyChanged()");
    }

    void AutomaticProperty_PropertySetterWasCalled_ChangesItsUnderlyingMember() {
        const bool propertyChanged = setProperty("AutomaticProperty", ExpectedValue);

        QCOMPARE(propertyChanged, true);
        QCOMPARE(m_AutomaticProperty, ExpectedValue);
    }

    void AutomaticProperty_SetterMethodWasCalled_ChangesItsUnderlyingMember() {
        SetAutomaticProperty(ExpectedValue);

        QCOMPARE(m_AutomaticProperty, ExpectedValue);
    }

    void AutomaticProperty_PropertyGetterWasCalled_ReturnsItsUnderlyingMember() {
        m_AutomaticProperty = ExpectedValue;

        QCOMPARE(property("AutomaticProperty").toInt(), ExpectedValue);
    }

    void AutomaticProperty_GetterMethodWasCalled_ReturnsItsUnderlyingMember() {
        m_AutomaticProperty = ExpectedValue;

        QCOMPARE(GetAutomaticProperty(), ExpectedValue);
    }

    void AutomaticProperty_PropertySetterWasCalledTwiceWithSameValue_NotifiesOnlyOnce() {
        QSignalSpy notification(this, SIGNAL(AutomaticPropertyChanged()));

        setProperty("AutomaticProperty", ExpectedValue);
        setProperty("AutomaticProperty", ExpectedValue);

        QTRY_COMPARE_WITH_TIMEOUT(notification.count(), 1, NotificationTimeout);
    }

    void AutomaticProperty_SetterMethodWasCalledTwiceWithSameValue_NotifiesOnlyOnce() {
        QSignalSpy notification(this, SIGNAL(AutomaticPropertyChanged()));

        SetAutomaticProperty(ExpectedValue);
        SetAutomaticProperty(ExpectedValue);

        QTRY_COMPARE_WITH_TIMEOUT(notification.count(), 1, NotificationTimeout);
    }

    void ReadonlyProperty_Exists_IsReadable() {
        const QMetaProperty property = GetProperty("ReadonlyProperty");

        QCOMPARE(property.isReadable(), true);
    }

    void ReadonlyProperty_Exists_IsNotWritable() {
        const QMetaProperty property = GetProperty("ReadonlyProperty");

        QCOMPARE(property.isWritable(), false);
    }

    void ReadonlyProperty_Exists_HasNotifySignal() {
        const QMetaProperty property = GetProperty("ReadonlyProperty");

        QVERIFY(property.hasNotifySignal());
        QCOMPARE(property.notifySignal().methodSignature(), "ReadonlyPropertyChanged()");
    }

    void ReadonlyProperty_PropertySetterWasCalled_ChangesNothing() {
        IgnoreWarningByWildcard("*ReadonlyProperty* invalid, read-only or does not exist");

        const bool propertyChanged = setProperty("ReadonlyProperty", ExpectedValue);

        QCOMPARE(propertyChanged, false);
        QCOMPARE(m_ReadonlyProperty, 0);
    }

    void ReadonlyProperty_SetterMethodWasCalled_ChangesItsUnderlyingMember() {
        SetReadonlyProperty(ExpectedValue);

        QCOMPARE(m_ReadonlyProperty, ExpectedValue);
    }

    void ReadonlyProperty_PropertyGetterWasCalled_ReturnsItsUnderlyingMember() {
        m_ReadonlyProperty = ExpectedValue;

        QCOMPARE(property("ReadonlyProperty").toInt(), ExpectedValue);
    }

    void ReadonlyProperty_GetterMethodWasCalled_ReturnsItsUnderlyingMember() {
        m_ReadonlyProperty = ExpectedValue;

        QCOMPARE(GetReadonlyProperty(), ExpectedValue);
    }

    void ReadonlyProperty_SetterMethodWasCalledTwiceWithSameValue_NotifiesOnlyOnce() {
        QSignalSpy notification(this, SIGNAL(ReadonlyPropertyChanged()));

        SetReadonlyProperty(ExpectedValue);
        SetReadonlyProperty(ExpectedValue);

        QTRY_COMPARE_WITH_TIMEOUT(notification.count(), 1, NotificationTimeout);
    }

private:
    static QMetaProperty GetProperty(const char *name) {
        return staticMetaObject.property(staticMetaObject.indexOfProperty(name));
    }

    static void IgnoreWarningByWildcard(const QString &messagePattern) {
        const auto regexPattern = QRegularExpression::wildcardToRegularExpression(messagePattern);
        QTest::ignoreMessage(QtWarningMsg, QRegularExpression(regexPattern));
    }

    static constexpr int ExpectedValue = 42;
    static constexpr int NotificationTimeout = 1000;
};

QTEST_MAIN(PropertyHelperTests)

#include "PropertyHelperTests.moc"
