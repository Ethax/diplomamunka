#ifndef BASICPORTTESTS_H
#define BASICPORTTESTS_H

#include <BasicPort.h>
#include <gmock/gmock.h>

namespace Diplomamunka::UnitTest {

class TestableBasicPort : public BasicPort {
    Q_OBJECT

public:
    MOCK_METHOD(QStringList, GetPortNames, (), (const, override));
    MOCK_METHOD(void, OpenPort, (const QString&), (override));
    MOCK_METHOD(QByteArray, ReadData, (), (override));
    MOCK_METHOD(void, WriteData, (const QByteArray&), (override));
};

class BasicPortTests : public testing::Test {
protected:
    BasicPortTests();

    testing::NiceMock<TestableBasicPort> m_BasicPort;

    const QStringList m_FakePorts {"COM1", "COM2"};
    const QString m_InvalidPort {"COM3"};
    const QByteArray m_TestData {"TEST"};
};

} // namespace Diplomamunka::UnitTest

#endif // BASICPORTTESTS_H
