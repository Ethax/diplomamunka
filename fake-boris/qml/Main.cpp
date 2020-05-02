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
    engine.load(QUrl("qrc:/MainWindow.qml"));

    return application.exec();
}
