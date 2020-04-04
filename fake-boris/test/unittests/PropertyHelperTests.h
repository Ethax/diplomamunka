#ifndef PROPERTYHELPERTESTS_H
#define PROPERTYHELPERTESTS_H

#include <PropertyHelper.hpp>
#include <QMetaProperty>
#include <gmock/gmock.h>

namespace Diplomamunka::UnitTest {

constexpr int TestValue = 42;

class PropertyHelperTests : public QObject, public testing::Test {
    Q_OBJECT

protected:
    QMetaProperty metaProperty(const char* name) {
        return metaObject()->property(metaObject()->indexOfProperty(name));
    }
};

class AutomaticPropertyTests : public PropertyHelperTests {
    Q_OBJECT
    AUTOMATIC_PROPERTY(int, automaticProperty) = 0;

    FRIEND_TEST(AutomaticPropertyTests, SetProperty_Called_ChangesItsUnderlyingMember);
    FRIEND_TEST(AutomaticPropertyTests, AutomaticProperty_Called_ChangesItsUnderlyingMember);
    FRIEND_TEST(AutomaticPropertyTests, Property_Called_ReturnsItsUnderlyingMember);
    FRIEND_TEST(AutomaticPropertyTests, AutomaticProperty_Called_ReturnsItsUnderlyingMember);
};

class ReadonlyPropertyTests : public PropertyHelperTests {
    Q_OBJECT
    READONLY_PROPERTY(int, readonlyProperty) = 0;

    FRIEND_TEST(ReadonlyPropertyTests, SetProperty_Called_ChangesNothing);
    FRIEND_TEST(ReadonlyPropertyTests, ReadonlyProperty_Called_ChangesItsUnderlyingMember);
    FRIEND_TEST(ReadonlyPropertyTests, Property_Called_ReturnsItsUnderlyingMember);
    FRIEND_TEST(ReadonlyPropertyTests, ReadonlyProperty_Called_ReturnsItsUnderlyingMember);
    FRIEND_TEST(ReadonlyPropertyTests, ReadonlyProperty_CalledTwiceWithSameValue_NotifiesOnce);
};

} // namespace Diplomamunka::UnitTest

#endif // PROPERTYHELPERTESTS_H
