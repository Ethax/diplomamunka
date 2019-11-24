#include <QBuffer>
#include <QSignalSpy>
#include <QtTest>
#include <boris_controller.h>
#include <fakeit.hpp>
#include <memory>

using namespace diplomamunka;
using namespace fakeit;

class TestableBorisController final : public BorisController {
    Q_OBJECT
public:
    explicit TestableBorisController(ConnectionProvider &connection)
        : BorisController(connection, nullptr) {}

signals:
    void timerEventOccurred();

protected:
    void timerEvent(QTimerEvent *event) override {
        BorisController::timerEvent(event);
        killTimer(m_TimerId);
        emit timerEventOccurred();
    }
};

class FakeableIODevice : public QIODevice {
public:
    using QIODevice::writeData;
};

class BorisControllerTests : public QObject {
    Q_OBJECT

private slots:
#if 0
    void init() {
        //_fakeDevice = std::make_unique<QBuffer>();

        m_fakeConnection = std::make_unique<Mock<ConnectionProvider>>();
        When(Method((*m_fakeConnection), connection)).AlwaysReturn(m_fakeDevice->get());
        When(Method((*m_fakeConnection), open)).AlwaysReturn(true);
        Fake(Method((*m_fakeConnection), close));

        m_borisController = std::make_unique<BorisController>(m_fakeConnection->get());
    }
#endif

    void propertySetters_Invoked_EmitNotificationOnlyWhenChangeHasOccurred_data() {
        QTest::addColumn<QString>("property");
        QTest::addColumn<QVariant>("value");
        QTest::addColumn<QString>("signal");

        QTest::newRow("output") << "output" << QVariant(0x1234) << SIGNAL(outputChanged());
    }

    void propertySetters_Invoked_EmitNotificationOnlyWhenChangeHasOccurred() {
        QFETCH(QString, property);
        QFETCH(QVariant, value);
        QFETCH(QString, signal);

        Mock<ConnectionProvider> fakeConnection;
        BorisController controller(fakeConnection.get());
        QSignalSpy notifications(&controller, signal.toUtf8());

        controller.setProperty(property.toUtf8(), value);
        controller.setProperty(property.toUtf8(), value);

        QTest::qWait(10);
        QCOMPARE(notifications.count(), 1);
    }

    void beginTransaction_ConnectionFailed_ReturnsFalse() {
        Mock<ConnectionProvider> fakeConnection;
        When(Method(fakeConnection, connect)).Return(false);
        BorisController controller(fakeConnection.get());

        const bool transactionHasBegun = controller.beginTransaction("Foo");

        QCOMPARE(transactionHasBegun, false);
    }

    void beginTransaction_ConnectionSucceeded_StartsSendingTheOutput() {
        QBuffer fakeDevice;
        fakeDevice.open(QIODevice::ReadWrite);

        Mock<ConnectionProvider> fakeConnection;
        When(Method(fakeConnection, connection)).Return(fakeDevice);
        When(Method(fakeConnection, connect).Using("Foo")).Return(true);

        TestableBorisController controller(fakeConnection.get());
        // controller.makeSchedulerSingleShot();

        controller.setOutput(0x1234);
        controller.beginTransaction("Foo");

        QTest::qWait(10);
        QVERIFY(fakeDevice.buffer().startsWith("\x12\x34"));
    }

#if 0
private:
    void simulateDataArrival(const QByteArray &incomingData) {
        When(Method((*m_fakeDevice), readAll)).Return(incomingData);
        emit m_fakeDevice->get().readyRead();
    }

    std::unique_ptr<Mock<QIODevice>> m_fakeDevice;
    std::unique_ptr<Mock<ConnectionProvider>> m_fakeConnection;
    std::unique_ptr<BorisController> m_borisController;
#endif
};

#if 0
class FakeBorisTests : public QObject {
    Q_OBJECT

private slots:
    void init() {
        m_ioDeviceMock = std::make_unique<QBuffer>();
        m_borisController = std::make_unique<BorisController>(*m_ioDeviceMock);
    }

    void setOutput_NewOutputIsDifferent_SignalsTheChange() {
        QSignalSpy outputChanged(m_borisController.get(), &BorisController::outputChanged);

        m_borisController->setOutput(0xaaaa);

        QCOMPARE(outputChanged.count(), 1);
    }

    void setOutput_NewOutputIsTheSame_DoesNotSignal() {
        QSignalSpy outputChanged(m_borisController.get(), &BorisController::outputChanged);

        m_borisController->setOutput(0);

        QCOMPARE(outputChanged.count(), 0);
    }

    void inputReceived_NewInputIsDifferent_SignalsTheChange() {
        QSignalSpy inputChanged(m_borisController.get(), &BorisController::inputChanged);
        m_ioDeviceMock->setData("\xaa\xaa");
        m_ioDeviceMock->open(QIODevice::ReadWrite);

        emit m_ioDeviceMock->readyRead();

        QCOMPARE(inputChanged.count(), 1);
    }

    void inputReceived_NewInputIsTheSame_DoesNotSignal() {
        QSignalSpy inputChanged(m_borisController.get(), &BorisController::inputChanged);
        m_ioDeviceMock->setData("\x00\x00");
        m_ioDeviceMock->open(QIODevice::ReadWrite);

        emit m_ioDeviceMock->readyRead();

        QCOMPARE(inputChanged.count(), 0);
    }

    void inputReceived_IncorrectInputLenght_DropsInput_data() {
        QTest::addColumn<QByteArray>("input");
        QTest::newRow("one byte") << QByteArray("\xaa");
        QTest::newRow("three bytes") << QByteArray("\xaa\x33\xff");
    }

    void inputReceived_IncorrectInputLenght_DropsInput() {
        QSignalSpy inputChanged(m_borisController.get(), &BorisController::inputChanged);
        QFETCH(QByteArray, input);
        m_ioDeviceMock->setData(input);
        m_ioDeviceMock->open(QIODevice::ReadWrite);

        emit m_ioDeviceMock->readyRead();

        QCOMPARE(inputChanged.count(), 0);
    }

private:
    std::unique_ptr<QBuffer> m_ioDeviceMock;
    std::unique_ptr<BorisController> m_borisController;
};

QTEST_APPLESS_MAIN(FakeBorisTests)
#endif

QTEST_MAIN(BorisControllerTests)
#include "boris_controller_tests.moc"
