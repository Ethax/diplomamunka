#include <BorisController.h>
#include <QCoreApplication>
#include <QtTest>
#include <fakeit.hpp>

using namespace Diplomamunka;
using namespace fakeit;

namespace {

class TestableBorisController : public AbstractBorisController {
public:
    Mock<IOPort> FakeIOPort;
    Mock<Timer> FakeTimer;

private:
    IOPort &GetIOPort() override { return FakeIOPort.get(); }
    Timer &GetTimer() override { return FakeTimer.get(); }
    const IOPort &GetIOPort() const override { return m_IOPortConstRef; }
    const Timer &GetTimer() const override { return m_TimerConstRef; }

    const IOPort &m_IOPortConstRef = FakeIOPort.get();
    const Timer &m_TimerConstRef = FakeTimer.get();
};

} // namespace

class BorisControllerTests : public QObject {
    Q_OBJECT

private slots:
    void test_case1() {
        TestableBorisController fakeController;
        When(Method(fakeController.FakeIOPort, Open)).Throw(std::runtime_error(""));
    }
};

QTEST_MAIN(BorisControllerTests)

#include "BorisControllerTests.moc"
