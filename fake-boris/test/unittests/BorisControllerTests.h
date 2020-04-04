#ifndef BORISCONTROLLERTESTS_H
#define BORISCONTROLLERTESTS_H

#include <BorisController.h>
#include <gmock/gmock.h>

namespace Diplomamunka::UnitTest {

class FakeIOPort : public IOPort {
    Q_OBJECT

public:
    MOCK_METHOD(QStringList, getPortNames, (), (const, override));
    MOCK_METHOD(void, open, (const QString&), (override));
    MOCK_METHOD(bool, isOpen, (), (const, override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(QByteArray, read, (), (override));
    MOCK_METHOD(void, write, (const QByteArray&), (override));
};

using FakeIOPortPtr = std::shared_ptr<FakeIOPort>;

class FakeTimer : public Timer {
    Q_OBJECT

public:
    MOCK_METHOD(void, start, (int), (override));
    MOCK_METHOD(bool, isRunning, (), (const, override));
    MOCK_METHOD(void, stop, (), (override));
};

using FakeTimerPtr = std::shared_ptr<FakeTimer>;

class BorisControllerTests : public testing::Test {
protected:
    FakeIOPortPtr m_ioPortPtr = std::make_shared<testing::NiceMock<FakeIOPort>>();
    FakeTimerPtr m_timerPtr = std::make_shared<testing::NiceMock<FakeTimer>>();
};

} // namespace Diplomamunka::UnitTest

#endif // BORISCONTROLLERTESTS_H
