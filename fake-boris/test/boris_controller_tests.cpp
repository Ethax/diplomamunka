#include <QBuffer>
#include <QSignalSpy>
#include <QtTest>
#include <boris_controller.h>
#include <fakeit.hpp>
#include <memory>

using namespace diplomamunka;
using namespace fakeit;

class BorisControllerTests : public QObject {
    Q_OBJECT

private slots:
    void init() {
        m_fakeDevice = std::make_unique<QBuffer>();

        m_fakeConnection = std::make_unique<Mock<ConnectionProvider>>();
        When(Method((*m_fakeConnection), connection)).AlwaysReturn(*m_fakeDevice);
        When(Method((*m_fakeConnection), open)).AlwaysReturn(true);
        Fake(Method((*m_fakeConnection), close));

        m_borisController = std::make_unique<BorisController>(m_fakeConnection->get());
    }

    void setOutput_WhenInvoked_IgnoresValuesEqualToCurrentValue() {
        QSignalSpy outputChanged(m_borisController.get(), &BorisController::outputChanged);

        m_borisController->setOutput(0xabcd);
        m_borisController->setOutput(0x1234);
        m_borisController->setOutput(0x1234);

        QCOMPARE(outputChanged.count(), 2);
    }

    // beginTransaction calls open
    // endTransaction calls close
    // destructor closes the transaction

private:
    void simulateDataArrival(QByteArray &&incomingData) {
        m_fakeDevice->buffer() = incomingData;
        m_fakeDevice->seek(0);
        emit m_fakeDevice->readyRead();
    }

    std::unique_ptr<QBuffer> m_fakeDevice;
    std::unique_ptr<Mock<ConnectionProvider>> m_fakeConnection;
    std::unique_ptr<BorisController> m_borisController;
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

QTEST_APPLESS_MAIN(BorisControllerTests)
#include "boris_controller_tests.moc"
