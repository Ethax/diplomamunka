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
    IOPort &GetIOPort() override { return m_IOPort; }
    Timer &GetTimer() override { return m_Timer; }
    const IOPort &GetIOPort() const override { return m_IOPort; }
    const Timer &GetTimer() const override { return m_Timer; }

    IOPort &m_IOPort = FakeIOPort.get();
    Timer &m_Timer = FakeTimer.get();
};

} // namespace

namespace QTest {

template <typename T> auto getData(const char *name) {
    return *static_cast<T *>(qData(name, qMetaTypeId<T>()));
}

} // namespace QTest

class BorisControllerTests : public QObject {
    Q_OBJECT

private slots:

    // TODO: Testing IsActive is not necessary

    void IsActive_PortIsOpenAndTimerIsRunning_ReturnsTrue() {
        TestableBorisController controller;
        When(Method(controller.FakeIOPort, IsOpen)).Return(true);
        When(Method(controller.FakeTimer, IsRunning)).Return(true);

        const bool controllerIsActive = controller.IsActive();

        QCOMPARE(controllerIsActive, true);
    }

    void IsActive_PortIsNotOpenOrTimerIsNotRunning_ReturnsFalse_data() {
        QTest::addColumn<bool>("IsOpen");
        QTest::addColumn<bool>("IsRunning");

        QTest::newRow("PortIsNotOpen") << false << true;
        QTest::newRow("TimerIsNotRunning") << true << false;
        QTest::newRow("PortIsNotOpenAndTimerIsNotRunning") << false << false;
    }

    void IsActive_PortIsNotOpenOrTimerIsNotRunning_ReturnsFalse() {
        TestableBorisController controller;
        When(Method(controller.FakeIOPort, IsOpen)).Return(QTest::getData<bool>("IsOpen"));
        When(Method(controller.FakeTimer, IsRunning)).Return(QTest::getData<bool>("IsRunning"));

        const bool controllerIsActive = controller.IsActive();

        QCOMPARE(controllerIsActive, false);
    }
};

QTEST_MAIN(BorisControllerTests)

#include "BorisControllerTests.moc"
