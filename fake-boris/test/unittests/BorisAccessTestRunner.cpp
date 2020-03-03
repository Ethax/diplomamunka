#include <QCoreApplication>
#include <QTimer>
#include <gmock/gmock.h>

using namespace testing;

int main(int argc, char *argv[]) {
    QCoreApplication application{argc, argv};

    QTimer::singleShot(0, [&]() {
        InitGoogleMock(&argc, argv);

        auto testResult = RUN_ALL_TESTS();
        application.exit(testResult);
    });

    return application.exec();
}
