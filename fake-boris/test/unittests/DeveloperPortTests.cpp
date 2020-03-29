#include <DeveloperPortTests.h>
#include <Exception.h>

using namespace testing;
using namespace Diplomamunka;

namespace Diplomamunka::UnitTest {

TEST_F(DeveloperPortTests, IsOpen_PortHasBeenOpened_ReturnsTrue) {
    m_DeveloperPort.Open(m_FakePorts.first());

    ASSERT_THAT(m_DeveloperPort.IsOpen(), IsTrue());
}

TEST_F(DeveloperPortTests, IsOpen_PortHasBeenClosed_ReturnsFalse) {
    m_DeveloperPort.Open(m_FakePorts.first());
    m_DeveloperPort.Close();

    ASSERT_THAT(m_DeveloperPort.IsOpen(), IsFalse());
}

TEST_F(DeveloperPortTests, Open_PortIsAlreadyOpen_ThrowsException) {
    m_DeveloperPort.Open(m_FakePorts.first());

    ASSERT_THROW(m_DeveloperPort.Open(m_FakePorts.last()), InvalidOperationException);
}

TEST_F(DeveloperPortTests, Open_PortNameIsInvalid_ThrowsException) {
    ASSERT_THROW(m_DeveloperPort.Open(m_InvalidPort), ArgumentException);
}

TEST_F(DeveloperPortTests, Open_PortCanBeOpened_CallsOpenPort) {
    EXPECT_CALL(m_DeveloperPort, OpenPort(m_FakePorts.first()));

    m_DeveloperPort.Open(m_FakePorts.first());
}

TEST_F(DeveloperPortTests, Close_PortIsNotOpen_ThrowsException) {
    ASSERT_THROW(m_DeveloperPort.Close(), InvalidOperationException);
}

TEST_F(DeveloperPortTests, Read_PortIsNotOpen_ThrowsException) {
    ASSERT_THROW(m_DeveloperPort.Read(), IOException);
}

TEST_F(DeveloperPortTests, Read_PortIsOpen_CallsReadData) {
    EXPECT_CALL(m_DeveloperPort, ReadData());

    m_DeveloperPort.Open(m_FakePorts.first());

    m_DeveloperPort.Read();
}

TEST_F(DeveloperPortTests, Write_PortIsNotOpen_ThrowsException) {
    ASSERT_THROW(m_DeveloperPort.Write(m_TestData), IOException);
}

TEST_F(DeveloperPortTests, Write_PortIsOpen_CallsWriteData) {
    EXPECT_CALL(m_DeveloperPort, WriteData(m_TestData));

    m_DeveloperPort.Open(m_FakePorts.first());

    m_DeveloperPort.Write(m_TestData);
}

DeveloperPortTests::DeveloperPortTests() {
    ON_CALL(m_DeveloperPort, GetPortNames()).WillByDefault(Return(m_FakePorts));
}

} // namespace Diplomamunka::UnitTest
