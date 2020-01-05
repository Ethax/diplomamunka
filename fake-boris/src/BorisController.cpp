#include <BorisController.h>

using namespace Diplomamunka;

AbstractBorisController::AbstractBorisController(QObject *parent) : QObject(parent) {}

void AbstractBorisController::Start() {}

bool AbstractBorisController::IsActive() const {
    return GetIOPort().IsOpen() && GetTimer().IsRunning();
}

BorisController::BorisController(QObject *parent) : AbstractBorisController(parent) {}
