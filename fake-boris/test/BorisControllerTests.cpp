#include <BorisController.h>
#include <Exception.h>
#include <QCoreApplication>
#include <QtTest>
#include <fakeit.hpp>

using namespace Diplomamunka;
using namespace fakeit;

namespace {

Mock<IOPort> CreateFakeIOPort();
Mock<Timer> CreateFakeTimer();

class TestableBorisController : public AbstractBorisController {
public:
    Mock<IOPort> FakeIOPort = CreateFakeIOPort();
    Mock<Timer> FakeTimer = CreateFakeTimer();

private:
    IOPort &GetIOPort() override { return FakeIOPort.get(); }
    Timer &GetTimer() override { return FakeTimer.get(); }
};

} // namespace

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
};

namespace {

Mock<IOPort> CreateFakeIOPort() {
    Mock<IOPort> fakeIOPort;
    Fake(Method(fakeIOPort, GetPortNames));
    Fake(Method(fakeIOPort, Open));
    Fake(Method(fakeIOPort, IsOpen));
    Fake(Method(fakeIOPort, Close));
    Fake(Method(fakeIOPort, Read));
    Fake(Method(fakeIOPort, Write));
    return fakeIOPort;
}

Mock<Timer> CreateFakeTimer() {
    Mock<Timer> fakeTimer;
    Fake(Method(fakeTimer, Start));
    Fake(Method(fakeTimer, IsRunning));
    Fake(Method(fakeTimer, Stop));
    return fakeTimer;
}

} // namespace

QTEST_MAIN(BorisControllerTests)

#include "BorisControllerTests.moc"
