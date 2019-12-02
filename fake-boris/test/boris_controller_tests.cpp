#include <QBuffer>
#include <QSignalSpy>
#include <QtTest>
#include <array>
#include <boris_controller.h>
#include <fakeit.hpp>
#include <memory>

using namespace diplomamunka;
using namespace fakeit;
using namespace QTest;

namespace {
template <typename T> auto getData(const char *name) {
    return *static_cast<T *>(qData(name, qMetaTypeId<T>()));
}
} // namespace

class BorisControllerTests : public QObject {
    Q_OBJECT

private slots:
    void propertySetters_Invoked_EmitNotificationOnlyWhenChangeHasOccurred_data() {
        addColumn<QString>("property");
        addColumn<QVariant>("value");
        addColumn<QString>("signal");

        newRow("setOutput") << "output" << QVariant(0x1234) << SIGNAL(outputChanged());
        newRow("setInterval") << "interval" << QVariant(1234) << SIGNAL(intervalChanged());
    }

    void propertySetters_Invoked_EmitNotificationOnlyWhenChangeHasOccurred() {
        const auto property = getData<QString>("property").toUtf8();
        const auto value = getData<QVariant>("value");
        const auto signal = getData<QString>("signal").toUtf8();

        Mock<ConnectionProvider> fakeConnection;
        BorisController controller(fakeConnection.get());
        QSignalSpy notifications(&controller, signal);
        Fake(Method(fakeConnection, disconnect));

        controller.setProperty(property, value);
        controller.setProperty(property, value);

        QTRY_COMPARE_WITH_TIMEOUT(notifications.count(), 1, 10);
    }

    void beginTransaction_ConnectionFailed_ReturnsFalse() {
        Mock<ConnectionProvider> fakeConnection;
        BorisController controller(fakeConnection.get());
        When(Method(fakeConnection, connect)).Return(false);
        Fake(Method(fakeConnection, disconnect));

        const bool transactionHasBegun = controller.beginTransaction("Foo");

        QCOMPARE(transactionHasBegun, false);
    }

    void beginTransaction_ConnectionSucceeded_StartsSendingTheOutput() {
        QBuffer fakeDevice;
        Mock<ConnectionProvider> fakeConnection;
        BorisController controller(fakeConnection.get());
        When(Method(fakeConnection, connection)).Return(fakeDevice);
        When(Method(fakeConnection, connect).Using("Foo")).Return(true);
        Fake(Method(fakeConnection, disconnect));

        fakeDevice.open(QIODevice::ReadWrite);
        controller.setInterval(10);
        controller.setOutput(0x1234);
        controller.beginTransaction("Foo");

        QTRY_COMPARE_WITH_TIMEOUT(fakeDevice.buffer(), "\xba\x12\x34\xb9", 15);
    }

    void endTransaction_OngoingTransaction_DisconnectsTheDevice() {
        QBuffer fakeDevice;
        Mock<ConnectionProvider> fakeConnection;
        BorisController controller(fakeConnection.get());
        When(Method(fakeConnection, connection)).Return(fakeDevice);
        When(Method(fakeConnection, connect).Using("Foo")).Return(true);
        Fake(Method(fakeConnection, disconnect));

        fakeDevice.open(QIODevice::ReadWrite);
        controller.beginTransaction("Foo");
        controller.endTransaction();

        Verify(Method(fakeConnection, disconnect)).Once();
    }

    void isActive_OngoingTransactionHasEnded_ReturnsFalse() {
        QBuffer fakeDevice;
        Mock<ConnectionProvider> fakeConnection;
        BorisController controller(fakeConnection.get());
        When(Method(fakeConnection, connection)).Return(fakeDevice);
        When(Method(fakeConnection, connect).Using("Foo")).Return(true);
        Fake(Method(fakeConnection, disconnect));

        fakeDevice.open(QIODevice::ReadWrite);
        controller.beginTransaction("Foo");
        controller.endTransaction();
        const bool transactionIsActive = controller.isActive();

        QCOMPARE(transactionIsActive, false);
    }

    void destructor_OngoingTransaction_DisconnectsTheDevice() {
        QBuffer fakeDevice;
        Mock<ConnectionProvider> fakeConnection;
        When(Method(fakeConnection, connection)).Return(fakeDevice);
        When(Method(fakeConnection, connect).Using("Foo")).Return(true);
        Fake(Method(fakeConnection, disconnect));

        fakeDevice.open(QIODevice::ReadWrite);
        {
            BorisController controller(fakeConnection.get());
            controller.beginTransaction("Foo");
        }

        Verify(Method(fakeConnection, disconnect)).Once();
    }
};

QTEST_MAIN(BorisControllerTests)
#include "boris_controller_tests.moc"
