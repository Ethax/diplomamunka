#include <PropertyHelperTests.h>
#include <QSignalSpy>

using namespace testing;

namespace Diplomamunka::UnitTest {

TEST_F(AutomaticPropertyTests, IsReadable_Called_ReturnsTrue) {
    ASSERT_THAT(m_AutomaticPropertyMeta.isReadable(), IsTrue());
}

TEST_F(ReadonlyPropertyTests, IsReadable_Called_ReturnsTrue) {
    ASSERT_THAT(m_ReadonlyPropertyMeta.isReadable(), IsTrue());
}

TEST_F(AutomaticPropertyTests, IsWritable_Called_ReturnsTrue) {
    ASSERT_THAT(m_AutomaticPropertyMeta.isWritable(), IsTrue());
}

TEST_F(ReadonlyPropertyTests, IsWritable_Called_ReturnsFalse) {
    ASSERT_THAT(m_ReadonlyPropertyMeta.isWritable(), IsFalse());
}

TEST_F(AutomaticPropertyTests, HasNotifySignal_Called_ReturnsTrue) {
    ASSERT_THAT(m_AutomaticPropertyMeta.hasNotifySignal(), IsTrue());
}

TEST_F(ReadonlyPropertyTests, HasNotifySignal_Called_ReturnsTrue) {
    ASSERT_THAT(m_ReadonlyPropertyMeta.hasNotifySignal(), IsTrue());
}

TEST_F(AutomaticPropertyTests, SetProperty_Called_ChangesItsUnderlyingMember) {
    const bool propertyChanged = setProperty("AutomaticProperty", ExpectedValue);

    ASSERT_THAT(propertyChanged, IsTrue());
    ASSERT_THAT(m_AutomaticProperty, Eq(ExpectedValue));
}

TEST_F(ReadonlyPropertyTests, SetProperty_Called_ChangesNothing) {
    const bool propertyChanged = setProperty("ReadonlyProperty", ExpectedValue);

    ASSERT_THAT(propertyChanged, IsFalse());
    ASSERT_THAT(m_ReadonlyProperty, Eq(0));
}

TEST_F(AutomaticPropertyTests, SetAutomaticProperty_Called_ChangesItsUnderlyingMember) {
    SetAutomaticProperty(ExpectedValue);

    ASSERT_THAT(m_AutomaticProperty, Eq(ExpectedValue));
}

TEST_F(ReadonlyPropertyTests, SetReadonlyProperty_Called_ChangesItsUnderlyingMember) {
    SetReadonlyProperty(ExpectedValue);

    ASSERT_THAT(m_ReadonlyProperty, Eq(ExpectedValue));
}

TEST_F(AutomaticPropertyTests, Property_Called_ReturnsItsUnderlyingMember) {
    m_AutomaticProperty = ExpectedValue;

    ASSERT_THAT(property("AutomaticProperty").toInt(), Eq(ExpectedValue));
}

TEST_F(ReadonlyPropertyTests, Property_Called_ReturnsItsUnderlyingMember) {
    m_ReadonlyProperty = ExpectedValue;

    ASSERT_THAT(property("ReadonlyProperty").toInt(), Eq(ExpectedValue));
}

TEST_F(AutomaticPropertyTests, GetAutomaticProperty_Called_ReturnsItsUnderlyingMember) {
    m_AutomaticProperty = ExpectedValue;

    ASSERT_THAT(GetAutomaticProperty(), Eq(ExpectedValue));
}

TEST_F(ReadonlyPropertyTests, GetReadonlyProperty_Called_ReturnsItsUnderlyingMember) {
    m_ReadonlyProperty = ExpectedValue;

    ASSERT_THAT(GetReadonlyProperty(), Eq(ExpectedValue));
}

TEST_F(AutomaticPropertyTests, SetAutomaticProperty_CalledTwiceWithSameValue_NotifiesOnce) {
    QSignalSpy notification(this, SIGNAL(AutomaticPropertyChanged()));

    SetAutomaticProperty(ExpectedValue);
    SetAutomaticProperty(ExpectedValue);

    ASSERT_THAT(notification.count(), Eq(1));
}

TEST_F(ReadonlyPropertyTests, SetReadonlyProperty_CalledTwiceWithSameValue_NotifiesOnce) {
    QSignalSpy notification(this, SIGNAL(ReadonlyPropertyChanged()));

    SetReadonlyProperty(ExpectedValue);
    SetReadonlyProperty(ExpectedValue);

    ASSERT_THAT(notification.count(), Eq(1));
}

TEST_F(AutomaticPropertyTests, SetProperty_CalledTwiceWithSameValue_NotifiesOnce) {
    QSignalSpy notification(this, SIGNAL(AutomaticPropertyChanged()));

    setProperty("AutomaticProperty", ExpectedValue);
    setProperty("AutomaticProperty", ExpectedValue);

    ASSERT_THAT(notification.count(), Eq(1));
}

} // namespace Diplomamunka::UnitTest
