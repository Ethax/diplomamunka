#include <BorisController.h>
#include <CyclicTimer.h>
#include <VirtualPort.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

using namespace Diplomamunka;

int main(int argc, char* argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication application(argc, argv);
    QQmlApplicationEngine engine;

#ifdef QT_DEBUG
    const auto port = VirtualPort::create();
    BorisController boris(port, CyclicTimer::create());

    engine.rootContext()->setContextProperty("port", port.get());
    engine.rootContext()->setContextProperty("boris", &boris);
    engine.load(QUrl("qrc:/MainWindow.qml"));
#else
    BorisController boris;

    engine.rootContext()->setContextProperty("boris", &boris);
    engine.load(QUrl("qrc:/MainWindow.qml"));
#endif

    return application.exec();
}
