#include <BorisController.h>
#include <Exception.h>

using namespace Diplomamunka;

AbstractBorisController::AbstractBorisController(QObject *parent) : QObject(parent) {}

void AbstractBorisController::Start() {
    try {
        GetIOPort().Open(GetPortName());
        GetTimer().Start(GetInterval());
    }
    catch (const Exception &) {
        GetTimer().Stop();
        GetIOPort().Close();
        throw;
    }
}

bool AbstractBorisController::IsActive() const {
    return GetIOPort().IsOpen() && GetTimer().IsRunning();
}

BorisController::BorisController(QObject *parent) : AbstractBorisController(parent) {}
