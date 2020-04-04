#include <PropertyHelperTests.h>
#include <QSignalSpy>

using namespace testing;

namespace Diplomamunka::UnitTest {

TEST_F(AutomaticPropertyTests, IsReadable_Called_ReturnsTrue) {
    const auto automaticProperty = metaProperty("automaticProperty");

    ASSERT_THAT(automaticProperty.isReadable(), IsTrue());
}

TEST_F(ReadonlyPropertyTests, IsReadable_Called_ReturnsTrue) {
    const auto readonlyProperty = metaProperty("readonlyProperty");

    ASSERT_THAT(readonlyProperty.isReadable(), IsTrue());
}

TEST_F(AutomaticPropertyTests, IsWritable_Called_ReturnsTrue) {
    const auto automaticProperty = metaProperty("automaticProperty");

    ASSERT_THAT(automaticProperty.isWritable(), IsTrue());
}

TEST_F(ReadonlyPropertyTests, IsWritable_Called_ReturnsFalse) {
    const auto readonlyProperty = metaProperty("readonlyProperty");

    ASSERT_THAT(readonlyProperty.isWritable(), IsFalse());
}

TEST_F(AutomaticPropertyTests, HasNotifySignal_Called_ReturnsTrue) {
    const auto automaticProperty = metaProperty("automaticProperty");

    ASSERT_THAT(automaticProperty.hasNotifySignal(), IsTrue());
}

TEST_F(ReadonlyPropertyTests, HasNotifySignal_Called_ReturnsTrue) {
    const auto readonlyProperty = metaProperty("readonlyProperty");

    ASSERT_THAT(readonlyProperty.hasNotifySignal(), IsTrue());
}

TEST_F(AutomaticPropertyTests, SetProperty_Called_ChangesItsUnderlyingMember) {
    const bool propertyChanged = setProperty("automaticProperty", TestValue);

    ASSERT_THAT(propertyChanged, IsTrue());
    ASSERT_THAT(m_automaticProperty, Eq(TestValue));
}

TEST_F(ReadonlyPropertyTests, SetProperty_Called_ChangesNothing) {
    const bool propertyChanged = setProperty("readonlyProperty", TestValue);

    ASSERT_THAT(propertyChanged, IsFalse());
    ASSERT_THAT(m_readonlyProperty, Eq(0));
}

TEST_F(AutomaticPropertyTests, AutomaticProperty_Called_ChangesItsUnderlyingMember) {
    automaticProperty(TestValue);

    ASSERT_THAT(m_automaticProperty, Eq(TestValue));
}

TEST_F(ReadonlyPropertyTests, ReadonlyProperty_Called_ChangesItsUnderlyingMember) {
    readonlyProperty(TestValue);

    ASSERT_THAT(m_readonlyProperty, Eq(TestValue));
}

TEST_F(AutomaticPropertyTests, Property_Called_ReturnsItsUnderlyingMember) {
    m_automaticProperty = TestValue;

    ASSERT_THAT(property("automaticProperty").toInt(), Eq(TestValue));
}

TEST_F(ReadonlyPropertyTests, Property_Called_ReturnsItsUnderlyingMember) {
    m_readonlyProperty = TestValue;

    ASSERT_THAT(property("readonlyProperty").toInt(), Eq(TestValue));
}

TEST_F(AutomaticPropertyTests, AutomaticProperty_Called_ReturnsItsUnderlyingMember) {
    m_automaticProperty = TestValue;

    ASSERT_THAT(automaticProperty(), Eq(TestValue));
}

TEST_F(ReadonlyPropertyTests, ReadonlyProperty_Called_ReturnsItsUnderlyingMember) {
    m_readonlyProperty = TestValue;

    ASSERT_THAT(readonlyProperty(), Eq(TestValue));
}

TEST_F(AutomaticPropertyTests, AutomaticProperty_CalledTwiceWithSameValue_NotifiesOnce) {
    QSignalSpy notification(this, SIGNAL(automaticPropertyChanged()));

    automaticProperty(TestValue);
    automaticProperty(TestValue);

    ASSERT_THAT(notification.count(), Eq(1));
}

TEST_F(ReadonlyPropertyTests, ReadonlyProperty_CalledTwiceWithSameValue_NotifiesOnce) {
    QSignalSpy notification(this, SIGNAL(readonlyPropertyChanged()));

    readonlyProperty(TestValue);
    readonlyProperty(TestValue);

    ASSERT_THAT(notification.count(), Eq(1));
}

TEST_F(AutomaticPropertyTests, SetProperty_CalledTwiceWithSameValue_NotifiesOnce) {
    QSignalSpy notification(this, SIGNAL(automaticPropertyChanged()));

    setProperty("automaticProperty", TestValue);
    setProperty("automaticProperty", TestValue);

    ASSERT_THAT(notification.count(), Eq(1));
}

} // namespace Diplomamunka::UnitTest
