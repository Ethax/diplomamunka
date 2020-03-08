#ifndef BORISCONTROLLERTESTS_H
#define BORISCONTROLLERTESTS_H

#include <BorisController.h>
#include <gmock/gmock.h>

namespace Diplomamunka::UnitTest {

class FakeIOPort : public IOPort {
    Q_OBJECT

public:
    MOCK_METHOD(QStringList, GetPortNames, (), (const, override));
    MOCK_METHOD(void, Open, (const QString&), (override));
    MOCK_METHOD(bool, IsOpen, (), (const, override));
    MOCK_METHOD(void, Close, (), (override));
    MOCK_METHOD(QByteArray, Read, (), (override));
    MOCK_METHOD(void, Write, (const QByteArray&), (override));
};

using FakeIOPortPtr = std::shared_ptr<FakeIOPort>;

class FakeTimer : public Timer {
    Q_OBJECT

public:
    MOCK_METHOD(void, Start, (int), (override));
    MOCK_METHOD(bool, IsRunning, (), (const, override));
    MOCK_METHOD(void, Stop, (), (override));
};

using FakeTimerPtr = std::shared_ptr<FakeTimer>;

class BorisControllerTests : public testing::Test {
protected:
    FakeIOPortPtr m_FakeIOPortPtr = std::make_shared<testing::NiceMock<FakeIOPort>>();
    FakeTimerPtr m_FakeTimerPtr = std::make_shared<testing::NiceMock<FakeTimer>>();
};

} // namespace Diplomamunka::UnitTest

#endif // BORISCONTROLLERTESTS_H
