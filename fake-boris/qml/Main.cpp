#include <BorisController.h>
#include <CyclicTimer.h>
#include <EchoPort.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

using namespace Diplomamunka;

int main(int argc, char* argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication application(argc, argv);
    QQmlApplicationEngine engine;

#ifdef QT_DEBUG
    BorisController boris(EchoPort::create(), CyclicTimer::create());
#else
    BorisController boris;
#endif
    engine.rootContext()->setContextProperty("boris", &boris);

    const QUrl url("qrc:/MainWindow.qml");
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &application,
        [url](QObject* object, const QUrl& objectUrl) {
            if (object == nullptr && objectUrl == url) {
                QCoreApplication::exit(-1);
            }
        },
        Qt::QueuedConnection);
    engine.load(url);

    return application.exec();
}
