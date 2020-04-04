#include <DeveloperPortTests.h>
#include <Exception.h>

using namespace testing;
using namespace Diplomamunka;

namespace Diplomamunka::UnitTest {

TEST_F(DeveloperPortTests, IsOpen_PortHasBeenOpened_ReturnsTrue) {
    m_DeveloperPort.open(FakePorts.first());

    ASSERT_THAT(m_DeveloperPort.isOpen(), IsTrue());
}

TEST_F(DeveloperPortTests, IsOpen_PortHasBeenClosed_ReturnsFalse) {
    m_DeveloperPort.open(FakePorts.first());
    m_DeveloperPort.close();

    ASSERT_THAT(m_DeveloperPort.isOpen(), IsFalse());
}

TEST_F(DeveloperPortTests, Open_PortIsAlreadyOpen_ThrowsException) {
    m_DeveloperPort.open(FakePorts.first());

    ASSERT_THROW(m_DeveloperPort.open(FakePorts.last()), InvalidOperationException);
}

TEST_F(DeveloperPortTests, Open_PortNameIsInvalid_ThrowsException) {
    ASSERT_THROW(m_DeveloperPort.open(InvalidPort), ArgumentException);
}

TEST_F(DeveloperPortTests, Open_PortCanBeOpened_CallsOpenPort) {
    EXPECT_CALL(m_DeveloperPort, openPort(FakePorts.first()));

    m_DeveloperPort.open(FakePorts.first());
}

TEST_F(DeveloperPortTests, Close_PortIsNotOpen_ThrowsException) {
    ASSERT_THROW(m_DeveloperPort.close(), InvalidOperationException);
}

TEST_F(DeveloperPortTests, Read_PortIsNotOpen_ThrowsException) {
    ASSERT_THROW(m_DeveloperPort.read(), IOException);
}

TEST_F(DeveloperPortTests, Read_PortIsOpen_CallsReadData) {
    EXPECT_CALL(m_DeveloperPort, readData());

    m_DeveloperPort.open(FakePorts.first());

    m_DeveloperPort.read();
}

TEST_F(DeveloperPortTests, Write_PortIsNotOpen_ThrowsException) {
    ASSERT_THROW(m_DeveloperPort.write(TestData), IOException);
}

TEST_F(DeveloperPortTests, Write_PortIsOpen_CallsWriteData) {
    EXPECT_CALL(m_DeveloperPort, writeData(TestData));

    m_DeveloperPort.open(FakePorts.first());

    m_DeveloperPort.write(TestData);
}

DeveloperPortTests::DeveloperPortTests() {
    ON_CALL(m_DeveloperPort, getPortNames()).WillByDefault(Return(FakePorts));
}

} // namespace Diplomamunka::UnitTest
