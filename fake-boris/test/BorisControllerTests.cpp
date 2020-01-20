#include <BorisController.h>
#include <Exception.h>
#include <QCoreApplication>
#include <QtTest>
#include <TestDummy.h>
#include <fakeit.hpp>

using namespace fakeit;

namespace Diplomamunka::UnitTest {

class BorisControllerTests : public QObject {
    Q_OBJECT

private slots:
    void Constructor_ProvidedIOPortPtrIsNullptr_ThrowsArgumentNullException() {
        Mock<Timer> fakeTimer;
        TimerPtr fakeTimerPtr(&fakeTimer(), [](...) {});

        QVERIFY_EXCEPTION_THROWN(BorisController(nullptr, fakeTimerPtr), ArgumentNullException);
    }

    void Constructor_ProvidedTimerPtrIsNullptr_ThrowsArgumentNullException() {
        Mock<IOPort> fakeIOPort;
        IOPortPtr fakeIOPortPtr(&fakeIOPort(), [](...) {});

        QVERIFY_EXCEPTION_THROWN(BorisController(fakeIOPortPtr, nullptr), ArgumentNullException);
    }

    void Destructor_Invoked_StopsTimerBeforeClosingPort() {
        CreateBorisController();

        Verify(Method(m_FakeTimer, Stop), Method(m_FakeIOPort, Close)).Once();
    }

    void Start_Invoked_OpensPortBeforeStartingTimer() {
        auto controller = CreateBorisController();

        controller.Start();

        Verify(Method(m_FakeIOPort, Open), Method(m_FakeTimer, Start)).Once();
    }

    void Stop_Invoked_StopsTimerBeforeClosingPort() {
        auto controller = CreateBorisController();

        controller.Stop();

        Verify(Method(m_FakeTimer, Stop), Method(m_FakeIOPort, Close)).Once();
    }

    void IsActive_ControllerStartedSuccessfully_ReturnsTrue() {
        auto controller = CreateBorisController();

        controller.Start();

        QCOMPARE(controller.IsActive(), true);
    }

    void IsActive_ControllerStartedThenStoppedSuccessfully_ReturnsFalse() {
        auto controller = CreateBorisController();

        controller.Start();
        controller.Stop();

        QCOMPARE(controller.IsActive(), false);
    }

    void IsActive_OpeningIOPortThrowsException_ReturnsFalse() {
        auto controller = CreateBorisController();
        When(Method(m_FakeIOPort, Open)).Throw(IOException("Test"));

        QVERIFY_EXCEPTION_THROWN(controller.Start(), IOException);
        QCOMPARE(controller.IsActive(), false);
    }

    void IsActive_StartingTimerThrowsException_ReturnsFalse() {
        auto controller = CreateBorisController();
        When(Method(m_FakeTimer, Start)).Throw(ArgumentOutOfRangeException("Test"));

        QVERIFY_EXCEPTION_THROWN(controller.Start(), ArgumentOutOfRangeException);
        QCOMPARE(controller.IsActive(), false);
    }

    void Output_CommunicationHasBeenStarted_AppearsInOutgoingData() {
        auto controller = CreateBorisController();
        controller.SetOutput(0x1234);

        controller.Start();
        emit m_FakeTimer.get().Elapsed();

        QTest::qWait(NotificationTimeout);
        Verify(Method(m_FakeIOPort, Write).Using("\xba\x12\x34\\xb9")).Once();
    }

    void init() {
        m_FakeIOPort.Reset();
        Fake(Method(m_FakeIOPort, GetPortNames));
        Fake(Method(m_FakeIOPort, Open));
        Fake(Method(m_FakeIOPort, IsOpen));
        Fake(Method(m_FakeIOPort, Close));
        Fake(Method(m_FakeIOPort, Read));
        Fake(Method(m_FakeIOPort, Write));

        m_FakeTimer.Reset();
        Fake(Method(m_FakeTimer, Start));
        Fake(Method(m_FakeTimer, IsRunning));
        Fake(Method(m_FakeTimer, Stop));
    }

private:
    BorisController CreateBorisController() {
        IOPortPtr fakeIOPortPtr(&m_FakeIOPort.get(), [](...) {});
        TimerPtr fakeTimerPtr(&m_FakeTimer.get(), [](...) {});

        return BorisController(fakeIOPortPtr, fakeTimerPtr);
    }

    DummyIOPort m_DummyIOPort;
    Mock<IOPort> m_FakeIOPort{m_DummyIOPort};

    DummyTimer m_DummyTimer;
    Mock<Timer> m_FakeTimer{m_DummyTimer};

    static constexpr int NotificationTimeout = 10;
};

} // namespace Diplomamunka::UnitTest

QTEST_MAIN(Diplomamunka::UnitTest::BorisControllerTests)

#include "BorisControllerTests.moc"
