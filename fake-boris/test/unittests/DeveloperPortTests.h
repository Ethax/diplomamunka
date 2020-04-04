#ifndef DEVELOPERPORTTESTS_H
#define DEVELOPERPORTTESTS_H

#include <DeveloperPort.h>
#include <gmock/gmock.h>

namespace Diplomamunka::UnitTest {

class TestableDeveloperPort : public DeveloperPort {
    Q_OBJECT

public:
    MOCK_METHOD(QStringList, getPortNames, (), (const, override));
    MOCK_METHOD(void, openPort, (const QString&), (override));
    MOCK_METHOD(QByteArray, readData, (), (override));
    MOCK_METHOD(void, writeData, (const QByteArray&), (override));
};

class DeveloperPortTests : public testing::Test {
protected:
    DeveloperPortTests();

    testing::NiceMock<TestableDeveloperPort> m_DeveloperPort;
};

inline const QStringList FakePorts {"COM1", "COM2"};
inline const QString InvalidPort {"COM3"};
inline const QByteArray TestData {"TEST"};

} // namespace Diplomamunka::UnitTest

#endif // DEVELOPERPORTTESTS_H
