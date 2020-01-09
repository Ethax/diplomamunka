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
        Stop();
        throw;
    }
}

bool AbstractBorisController::IsActive() const {
    return GetIOPort().IsOpen() && GetTimer().IsRunning();
}

void AbstractBorisController::Stop() {
    GetTimer().Stop();
    GetIOPort().Close();
}

BorisController::BorisController(QObject *parent) : AbstractBorisController(parent) {}
