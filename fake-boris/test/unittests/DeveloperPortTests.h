#ifndef DEVELOPERPORTTESTS_H
#define DEVELOPERPORTTESTS_H

#include <DeveloperPort.h>
#include <gmock/gmock.h>

namespace Diplomamunka::UnitTest {

class TestableDeveloperPort : public DeveloperPort {
    Q_OBJECT

public:
    MOCK_METHOD(QStringList, GetPortNames, (), (const, override));
    MOCK_METHOD(void, OpenPort, (const QString&), (override));
    MOCK_METHOD(QByteArray, ReadData, (), (override));
    MOCK_METHOD(void, WriteData, (const QByteArray&), (override));
};

class DeveloperPortTests : public testing::Test {
protected:
    DeveloperPortTests();

    testing::NiceMock<TestableDeveloperPort> m_DeveloperPort;

    const QStringList m_FakePorts {"COM1", "COM2"};
    const QString m_InvalidPort {"COM3"};
    const QByteArray m_TestData {"TEST"};
};

} // namespace Diplomamunka::UnitTest

#endif // DEVELOPERPORTTESTS_H
