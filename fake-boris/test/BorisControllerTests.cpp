#include <BorisController.h>
#include <Exception.h>
#include <QCoreApplication>
#include <QtTest>
#include <fakeit.hpp>

using namespace Diplomamunka;
using namespace fakeit;

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

        Verify(Method((*m_FakeTimer), Stop), Method((*m_FakeIOPort), Close)).Once();
    }

    void Start_Invoked_OpensPortBeforeStartingTimer() {
        auto controller = CreateBorisController();

        controller.Start();

        Verify(Method((*m_FakeIOPort), Open), Method((*m_FakeTimer), Start)).Once();
    }

    void Stop_Invoked_StopsTimerBeforeClosingPort() {
        auto controller = CreateBorisController();

        controller.Stop();

        Verify(Method((*m_FakeTimer), Stop), Method((*m_FakeIOPort), Close)).Once();
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
        When(Method((*m_FakeIOPort), Open)).Throw(IOException("Test"));

        QVERIFY_EXCEPTION_THROWN(controller.Start(), IOException);
        QCOMPARE(controller.IsActive(), false);
    }

    void IsActive_StartingTimerThrowsException_ReturnsFalse() {
        auto controller = CreateBorisController();
        When(Method((*m_FakeTimer), Start)).Throw(ArgumentOutOfRangeException("Test"));

        QVERIFY_EXCEPTION_THROWN(controller.Start(), ArgumentOutOfRangeException);
        QCOMPARE(controller.IsActive(), false);
    }

    void init() {
        m_FakeIOPort = std::make_unique<Mock<IOPort>>();
        Fake(Method((*m_FakeIOPort), GetPortNames));
        Fake(Method((*m_FakeIOPort), Open));
        Fake(Method((*m_FakeIOPort), IsOpen));
        Fake(Method((*m_FakeIOPort), Close));
        Fake(Method((*m_FakeIOPort), Read));
        Fake(Method((*m_FakeIOPort), Write));

        m_FakeTimer = std::make_unique<Mock<Timer>>();
        Fake(Method((*m_FakeTimer), Start));
        Fake(Method((*m_FakeTimer), IsRunning));
        Fake(Method((*m_FakeTimer), Stop));
    }

private:
    BorisController CreateBorisController() {
        IOPortPtr fakeIOPortPtr(&(*m_FakeIOPort)(), [](...) {});
        TimerPtr fakeTimerPtr(&(*m_FakeTimer)(), [](...) {});

        return BorisController(fakeIOPortPtr, fakeTimerPtr);
    }

    std::unique_ptr<Mock<IOPort>> m_FakeIOPort;
    std::unique_ptr<Mock<Timer>> m_FakeTimer;
};

QTEST_MAIN(BorisControllerTests)

#include "BorisControllerTests.moc"
