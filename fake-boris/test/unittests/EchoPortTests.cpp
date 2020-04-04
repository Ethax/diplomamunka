#include <EchoPort.h>
#include <gmock/gmock.h>

using namespace testing;
using namespace Diplomamunka;

namespace Diplomamunka::UnitTest {

TEST(EchoPortTests, NormalEcho_DataOfCorrectSizeWasUsed_EchoesPayload) {
    EchoPort port;
    port.open("ECHO (NORMAL)");

    port.write("\xff\xc0\xde\xff");

    ASSERT_THAT(port.read(), Eq("\xc0\xde"));
}

TEST(EchoPortTests, NormalEcho_TooShortDataWasUsed_EchoesDefaultData) {
    EchoPort port;
    port.open("ECHO (NORMAL)");

    port.write("\xc0\xde");

    ASSERT_THAT(port.read(), Eq(QByteArray(2, '\x00')));
}

TEST(EchoPortTests, NormalEcho_EmptyDataWasUsed_EchoesDefaultData) {
    EchoPort port;
    port.open("ECHO (NORMAL)");

    port.write("");

    ASSERT_THAT(port.read(), Eq(QByteArray(2, '\x00')));
}

TEST(EchoPortTests, InverseEcho_DataOfCorrectSizeWasUsed_EchoesInversePayload) {
    EchoPort port;
    port.open("ECHO (INVERSE)");

    port.write("\xff\xc0\xde\xff");

    ASSERT_THAT(port.read(), Eq("\x3f\x21"));
}

TEST(EchoPortTests, InverseEcho_TooShortDataWasUsed_EchoesDefaultData) {
    EchoPort port;
    port.open("ECHO (INVERSE)");

    port.write("\xc0\xde");

    ASSERT_THAT(port.read(), Eq(QByteArray(2, '\xff')));
}

TEST(EchoPortTests, InverseEcho_EmptyDataWasUsed_EchoesDefaultData) {
    EchoPort port;
    port.open("ECHO (INVERSE)");

    port.write("");

    ASSERT_THAT(port.read(), Eq(QByteArray(2, '\xff')));
}

} // namespace Diplomamunka::UnitTest
