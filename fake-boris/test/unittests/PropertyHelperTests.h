#ifndef PROPERTYHELPERTESTS_H
#define PROPERTYHELPERTESTS_H

#include <PropertyHelper.hpp>
#include <QMetaProperty>
#include <gmock/gmock.h>

namespace Diplomamunka::UnitTest {

constexpr int ExpectedValue = 42;

class AutomaticPropertyTests : public QObject, public testing::Test {
    Q_OBJECT
    AUTOMATIC_PROPERTY(int, AutomaticProperty) = 0;

    FRIEND_TEST(AutomaticPropertyTests, SetProperty_Called_ChangesItsUnderlyingMember);
    FRIEND_TEST(AutomaticPropertyTests, SetAutomaticProperty_Called_ChangesItsUnderlyingMember);
    FRIEND_TEST(AutomaticPropertyTests, Property_Called_ReturnsItsUnderlyingMember);
    FRIEND_TEST(AutomaticPropertyTests, GetAutomaticProperty_Called_ReturnsItsUnderlyingMember);

protected:
    const QMetaProperty m_AutomaticPropertyMeta {
        staticMetaObject.property(staticMetaObject.indexOfProperty("AutomaticProperty")) //
    };
};

class ReadonlyPropertyTests : public QObject, public testing::Test {
    Q_OBJECT
    READONLY_PROPERTY(int, ReadonlyProperty) = 0;

    FRIEND_TEST(ReadonlyPropertyTests, SetProperty_Called_ChangesNothing);
    FRIEND_TEST(ReadonlyPropertyTests, SetReadonlyProperty_Called_ChangesItsUnderlyingMember);
    FRIEND_TEST(ReadonlyPropertyTests, Property_Called_ReturnsItsUnderlyingMember);
    FRIEND_TEST(ReadonlyPropertyTests, GetReadonlyProperty_Called_ReturnsItsUnderlyingMember);
    FRIEND_TEST(ReadonlyPropertyTests, SetReadonlyProperty_CalledTwiceWithSameValue_NotifiesOnce);

protected:
    const QMetaProperty m_ReadonlyPropertyMeta {
        staticMetaObject.property(staticMetaObject.indexOfProperty("ReadonlyProperty")) //
    };
};

} // namespace Diplomamunka::UnitTest

#endif // PROPERTYHELPERTESTS_H
