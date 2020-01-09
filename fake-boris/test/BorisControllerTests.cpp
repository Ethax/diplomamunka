#include <BorisController.h>
#include <Exception.h>
#include <QCoreApplication>
#include <QtTest>
#include <fakeit.hpp>

using namespace Diplomamunka;
using namespace fakeit;

namespace {

class TestableBorisController : public AbstractBorisController {
public:
    TestableBorisController() : AbstractBorisController() {
        FakeIOPortMethods();
        FakeTimerMethods();
    }

    Mock<IOPort> FakeIOPort;
    Mock<Timer> FakeTimer;

private:
    IOPort &GetIOPort() override { return m_IOPort; }
    Timer &GetTimer() override { return m_Timer; }
    const IOPort &GetIOPort() const override { return m_IOPort; }
    const Timer &GetTimer() const override { return m_Timer; }

    void FakeIOPortMethods() {
        Fake(Method(FakeIOPort, GetPortNames));
        Fake(Method(FakeIOPort, Open));
        Fake(Method(FakeIOPort, IsOpen));
        Fake(Method(FakeIOPort, Close));
        Fake(Method(FakeIOPort, Read));
        Fake(Method(FakeIOPort, Write));
    }

    void FakeTimerMethods() {
        Fake(Method(FakeTimer, Start));
        Fake(Method(FakeTimer, IsRunning));
        Fake(Method(FakeTimer, Stop));
    }

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
    void Start_OpeningIOPortThrowsException_ClosesIOPortAndStopsTimer() {
        TestableBorisController controller;
        When(Method(controller.FakeIOPort, Open)).Throw(IOException("Test"));

        QVERIFY_EXCEPTION_THROWN(controller.Start(), IOException);
        Verify(Method(controller.FakeIOPort, Close)).Once();
        Verify(Method(controller.FakeTimer, Stop)).Once();
    }

    void Start_StartingTimerThrowsException_ClosesIOPortAndStopsTimer() {
        TestableBorisController controller;
        When(Method(controller.FakeTimer, Start)).Throw(ArgumentOutOfRangeException("Test"));

        QVERIFY_EXCEPTION_THROWN(controller.Start(), ArgumentOutOfRangeException);
        Verify(Method(controller.FakeTimer, Stop)).Once();
        Verify(Method(controller.FakeIOPort, Close)).Once();
    }

    void Start_Invoked_OpensPortBeforeStartingTimer() {
        TestableBorisController controller;

        controller.Start();

        Verify(Method(controller.FakeIOPort, Open), Method(controller.FakeTimer, Start));
    }

    void Stop_Invoked_StopsTimerBeforeClosingPort() {
        TestableBorisController controller;

        controller.Stop();

        Verify(Method(controller.FakeTimer, Stop), Method(controller.FakeIOPort, Close));
    }

    // TODO: Testing IsActive is not necessary
#if 0
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
#endif
};

QTEST_MAIN(BorisControllerTests)

#include "BorisControllerTests.moc"
