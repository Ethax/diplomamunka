#include <PropertyHelper.hpp>
#include <QMetaProperty>
#include <QSignalSpy>
#include <QTest>
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace testing;

namespace Diplomamunka::UnitTest {

class AutomaticProperty : public QObject, public Test {
    Q_OBJECT
    AUTOMATIC_PROPERTY(int, AutomaticProperty) = 0;

    const int m_PropertyIndex = staticMetaObject.indexOfProperty("AutomaticProperty");
    const QMetaProperty m_PropertyInfo = staticMetaObject.property(m_PropertyIndex);
};

class ReadonlyProperty : public QObject, public Test {
    Q_OBJECT
    READONLY_PROPERTY(int, ReadonlyProperty) = 0;

    const int m_PropertyIndex = staticMetaObject.indexOfProperty("ReadonlyProperty");
    const QMetaProperty m_PropertyInfo = staticMetaObject.property(m_PropertyIndex);
};

constexpr int ExpectedValue = 42;
constexpr int NotificationTimeout = 10;

TEST_F(AutomaticProperty, IsReadable) {
    ASSERT_THAT(m_PropertyInfo.isReadable(), Eq(true));
}

TEST_F(AutomaticProperty, IsWritable) {
    ASSERT_THAT(m_PropertyInfo.isWritable(), Eq(true));
}

TEST_F(AutomaticProperty, HasNotifySignal) {
    ASSERT_THAT(m_PropertyInfo.hasNotifySignal(), Eq(true));
    ASSERT_THAT(m_PropertyInfo.notifySignal().methodSignature(), Eq("AutomaticPropertyChanged()"));
}

TEST_F(AutomaticProperty, PropertySetterWasCalled_ChangesItsUnderlyingMember) {
    const bool propertyChanged = setProperty("AutomaticProperty", ExpectedValue);

    ASSERT_THAT(propertyChanged, Eq(true));
    ASSERT_THAT(m_AutomaticProperty, Eq(ExpectedValue));
}

TEST_F(AutomaticProperty, SetterMethodWasCalled_ChangesItsUnderlyingMember) {
    SetAutomaticProperty(ExpectedValue);

    ASSERT_THAT(m_AutomaticProperty, Eq(ExpectedValue));
}

TEST_F(AutomaticProperty, PropertyGetterWasCalled_ReturnsItsUnderlyingMember) {
    m_AutomaticProperty = ExpectedValue;

    ASSERT_THAT(property("AutomaticProperty").toInt(), Eq(ExpectedValue));
}

TEST_F(AutomaticProperty, GetterMethodWasCalled_ReturnsItsUnderlyingMember) {
    m_AutomaticProperty = ExpectedValue;

    ASSERT_THAT(GetAutomaticProperty(), Eq(ExpectedValue));
}

TEST_F(AutomaticProperty, PropertySetterWasCalledTwiceWithSameValue_NotifiesOnlyOnce) {
    QSignalSpy notification(this, SIGNAL(AutomaticPropertyChanged()));

    setProperty("AutomaticProperty", ExpectedValue);
    setProperty("AutomaticProperty", ExpectedValue);
    QTest::qWait(NotificationTimeout);

    ASSERT_THAT(notification.count(), Eq(1));
}

TEST_F(AutomaticProperty, SetterMethodWasCalledTwiceWithSameValue_NotifiesOnlyOnce) {
    QSignalSpy notification(this, SIGNAL(AutomaticPropertyChanged()));

    SetAutomaticProperty(ExpectedValue);
    SetAutomaticProperty(ExpectedValue);
    QTest::qWait(NotificationTimeout);

    ASSERT_THAT(notification.count(), Eq(1));
}

TEST_F(ReadonlyProperty, IsReadable) {
    ASSERT_THAT(m_PropertyInfo.isReadable(), Eq(true));
}

TEST_F(ReadonlyProperty, IsNotWritable) {
    ASSERT_THAT(m_PropertyInfo.isWritable(), Eq(false));
}

TEST_F(ReadonlyProperty, HasNotifySignal) {
    ASSERT_THAT(m_PropertyInfo.hasNotifySignal(), Eq(true));
    ASSERT_THAT(m_PropertyInfo.notifySignal().methodSignature(), Eq("ReadonlyPropertyChanged()"));
}

TEST_F(ReadonlyProperty, PropertySetterWasCalled_ChangesNothing) {
    const bool propertyChanged = setProperty("ReadonlyProperty", ExpectedValue);

    ASSERT_THAT(propertyChanged, Eq(false));
    ASSERT_THAT(m_ReadonlyProperty, Eq(0));
}

TEST_F(ReadonlyProperty, SetterMethodWasCalled_ChangesItsUnderlyingMember) {
    SetReadonlyProperty(ExpectedValue);

    ASSERT_THAT(m_ReadonlyProperty, Eq(ExpectedValue));
}

TEST_F(ReadonlyProperty, PropertyGetterWasCalled_ReturnsItsUnderlyingMember) {
    m_ReadonlyProperty = ExpectedValue;

    ASSERT_THAT(property("ReadonlyProperty").toInt(), Eq(ExpectedValue));
}

TEST_F(ReadonlyProperty, GetterMethodWasCalled_ReturnsItsUnderlyingMember) {
    m_ReadonlyProperty = ExpectedValue;

    ASSERT_THAT(GetReadonlyProperty(), Eq(ExpectedValue));
}

TEST_F(ReadonlyProperty, SetterMethodWasCalledTwiceWithSameValue_NotifiesOnlyOnce) {
    QSignalSpy notification(this, SIGNAL(ReadonlyPropertyChanged()));

    SetReadonlyProperty(ExpectedValue);
    SetReadonlyProperty(ExpectedValue);
    QTest::qWait(NotificationTimeout);

    ASSERT_THAT(notification.count(), Eq(1));
}

} // namespace Diplomamunka::UnitTest

#include "PropertyHelperTests.moc"
