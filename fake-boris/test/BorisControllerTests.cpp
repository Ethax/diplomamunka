#include <BorisController.h>
#include <Exception.h>
#include <QCoreApplication>
#include <QtTest>
#include <fakeit.hpp>

using namespace Diplomamunka;
using namespace fakeit;

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

template <typename T> std::shared_ptr<T> ToPtr(Mock<T> &fake) {
    return std::shared_ptr<T>(&fake(), [](...) {});
}

} // namespace

class BorisControllerTests : public QObject {
    Q_OBJECT

private slots:
    void Start_OpeningIOPortThrowsException_ClosesIOPortAndStopsTimer() {
        auto fakeIOPort = CreateFakeIOPort();
        auto fakeTimer = CreateFakeTimer();
        BorisController controller(ToPtr(fakeIOPort), ToPtr(fakeTimer));
        When(Method(fakeIOPort, Open)).Throw(IOException("Test"));

        QVERIFY_EXCEPTION_THROWN(controller.Start(), IOException);
        Verify(Method(fakeIOPort, Close)).Once();
        Verify(Method(fakeTimer, Stop)).Once();
    }

    void Start_StartingTimerThrowsException_ClosesIOPortAndStopsTimer() {
        auto fakeIOPort = CreateFakeIOPort();
        auto fakeTimer = CreateFakeTimer();
        BorisController controller(ToPtr(fakeIOPort), ToPtr(fakeTimer));
        When(Method(fakeTimer, Start)).Throw(ArgumentOutOfRangeException("Test"));

        QVERIFY_EXCEPTION_THROWN(controller.Start(), ArgumentOutOfRangeException);
        Verify(Method(fakeTimer, Stop)).Once();
        Verify(Method(fakeIOPort, Close)).Once();
    }

    void Start_Invoked_OpensPortBeforeStartingTimer() {
        auto fakeIOPort = CreateFakeIOPort();
        auto fakeTimer = CreateFakeTimer();
        BorisController controller(ToPtr(fakeIOPort), ToPtr(fakeTimer));

        controller.Start();

        Verify(Method(fakeIOPort, Open), Method(fakeTimer, Start));
    }

    void Stop_Invoked_StopsTimerBeforeClosingPort() {
        auto fakeIOPort = CreateFakeIOPort();
        auto fakeTimer = CreateFakeTimer();
        BorisController controller(ToPtr(fakeIOPort), ToPtr(fakeTimer));
        When(Method(fakeIOPort, IsOpen)).AlwaysReturn(true);
        When(Method(fakeTimer, IsRunning)).AlwaysReturn(true);

        controller.Stop();

        Verify(Method(fakeTimer, Stop), Method(fakeIOPort, Close));
    }
};

QTEST_MAIN(BorisControllerTests)

#include "BorisControllerTests.moc"
