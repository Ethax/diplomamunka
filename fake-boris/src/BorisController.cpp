#include <BorisController.h>
#include <Exception.h>

using namespace Diplomamunka;

AbstractBorisController::AbstractBorisController(QObject *parent) : QObject(parent) {}

void AbstractBorisController::Start() {
    try {
        GetIOPort().Open(GetPortName());
        GetTimer().Start(GetInterval());
        m_IsActive = true;
    }
    catch (const Exception &) {
        Stop();
        throw;
    }
}

void AbstractBorisController::Stop() {
    if (GetTimer().IsRunning()) {
        GetTimer().Stop();
    }
    if (GetIOPort().IsOpen()) {
        GetIOPort().Close();
    }
    m_IsActive = false;
}

BorisController::BorisController(QObject *parent) : AbstractBorisController(parent) {}

BorisController::~BorisController() {
    try {
        // TODO: direct calls to Stop and Close methods, avoid virtual methods
    }
    catch (...) {
    }
}
