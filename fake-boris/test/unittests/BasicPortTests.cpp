#include <BasicPortTests.h>
#include <Exception.h>

using namespace testing;
using namespace Diplomamunka;

namespace Diplomamunka::UnitTest {

TEST_F(BasicPortTests, IsOpen_PortHasBeenOpened_ReturnsTrue) {
    m_BasicPort.Open(m_FakePorts.first());

    ASSERT_THAT(m_BasicPort.IsOpen(), IsTrue());
}

TEST_F(BasicPortTests, IsOpen_PortHasBeenClosed_ReturnsFalse) {
    m_BasicPort.Open(m_FakePorts.first());
    m_BasicPort.Close();

    ASSERT_THAT(m_BasicPort.IsOpen(), IsFalse());
}

TEST_F(BasicPortTests, Open_PortIsAlreadyOpen_ThrowsException) {
    m_BasicPort.Open(m_FakePorts.first());

    ASSERT_THROW(m_BasicPort.Open(m_FakePorts.last()), InvalidOperationException);
}

TEST_F(BasicPortTests, Open_PortNameIsInvalid_ThrowsException) {
    ASSERT_THROW(m_BasicPort.Open(m_InvalidPort), ArgumentException);
}

TEST_F(BasicPortTests, Open_PortCanBeOpened_CallsOpenPort) {
    EXPECT_CALL(m_BasicPort, OpenPort(m_FakePorts.first()));

    m_BasicPort.Open(m_FakePorts.first());
}

TEST_F(BasicPortTests, Close_PortIsNotOpen_ThrowsException) {
    ASSERT_THROW(m_BasicPort.Close(), InvalidOperationException);
}

TEST_F(BasicPortTests, Read_PortIsNotOpen_ThrowsException) {
    ASSERT_THROW(m_BasicPort.Read(), IOException);
}

TEST_F(BasicPortTests, Read_PortIsOpen_CallsReadData) {
    EXPECT_CALL(m_BasicPort, ReadData());

    m_BasicPort.Open(m_FakePorts.first());

    m_BasicPort.Read();
}

TEST_F(BasicPortTests, Write_PortIsNotOpen_ThrowsException) {
    ASSERT_THROW(m_BasicPort.Write(m_TestData), IOException);
}

TEST_F(BasicPortTests, Write_PortIsOpen_CallsWriteData) {
    EXPECT_CALL(m_BasicPort, WriteData(m_TestData));

    m_BasicPort.Open(m_FakePorts.first());

    m_BasicPort.Write(m_TestData);
}

BasicPortTests::BasicPortTests() {
    ON_CALL(m_BasicPort, GetPortNames()).WillByDefault(Return(m_FakePorts));
}

} // namespace Diplomamunka::UnitTest
