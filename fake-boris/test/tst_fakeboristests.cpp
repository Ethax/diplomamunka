#include <QBuffer>
#include <QSignalSpy>
#include <QtTest>
#include <fakeboris.h>
#include <memory>

using namespace diplomamunka;

class FakeBorisTests : public QObject {
    Q_OBJECT

private slots:
    void init() {
        m_ioDeviceMock = std::make_unique<QBuffer>();
        m_fakeBoris = std::make_unique<FakeBoris>(*m_ioDeviceMock);
    }

    void setOutput_NewOutputIsDifferent_SignalsTheChange() {
        QSignalSpy outputChanged(m_fakeBoris.get(), &FakeBoris::outputChanged);

        m_fakeBoris->setOutput(0xaaaa);

        QCOMPARE(outputChanged.count(), 1);
    }

    void setOutput_NewOutputIsTheSame_DoesNotSignal() {
        QSignalSpy outputChanged(m_fakeBoris.get(), &FakeBoris::outputChanged);

        m_fakeBoris->setOutput(0);

        QCOMPARE(outputChanged.count(), 0);
    }

    void inputReceived_NewInputIsDifferent_SignalsTheChange() {
        QSignalSpy inputChanged(m_fakeBoris.get(), &FakeBoris::inputChanged);
        m_ioDeviceMock->setData("\xaa\xaa");
        m_ioDeviceMock->open(QIODevice::ReadWrite);

        emit m_ioDeviceMock->readyRead();

        QCOMPARE(inputChanged.count(), 1);
    }

    void inputReceived_NewInputIsTheSame_DoesNotSignal() {
        QSignalSpy inputChanged(m_fakeBoris.get(), &FakeBoris::inputChanged);
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
        QSignalSpy inputChanged(m_fakeBoris.get(), &FakeBoris::inputChanged);
        QFETCH(QByteArray, input);
        m_ioDeviceMock->setData(input);
        m_ioDeviceMock->open(QIODevice::ReadWrite);

        emit m_ioDeviceMock->readyRead();

        QCOMPARE(inputChanged.count(), 0);
    }

private:
    std::unique_ptr<QBuffer> m_ioDeviceMock;
    std::unique_ptr<FakeBoris> m_fakeBoris;
};

QTEST_APPLESS_MAIN(FakeBorisTests)
#include "tst_fakeboristests.moc"
