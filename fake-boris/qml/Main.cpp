#include <BorisController.h>
#include <CyclicTimer.h>
#include <EchoPort.h>

#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>

using namespace Diplomamunka;

int main(int argc, char* argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    BorisController boris(EchoPort::create(), CyclicTimer::create());

    engine.rootContext()->setContextProperty("boris", &boris);

    const QUrl url("qrc:/MainWindow.qml");
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
