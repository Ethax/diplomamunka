#include <BorisController.h>
#include <Exception.h>

using namespace Diplomamunka;

namespace {

template <typename T> void VerifyNotNullptr(const std::shared_ptr<T> &ptr, const QString &name) {
    if (ptr == nullptr) {
        throw ArgumentNullException(QString("Argument '%1' cannot be nullptr.").arg(name));
    }
}

} // namespace

// AbstractBorisController::AbstractBorisController(QObject *parent) : QObject(parent) {}

BorisController::BorisController(IOPortPtr ioPort, TimerPtr timer, QObject *parent)
    : QObject(parent), m_IOPort(ioPort), m_Timer(timer) {
    VerifyNotNullptr(ioPort, "ioPort");
    VerifyNotNullptr(timer, "timer");
}

void BorisController::Start() {
    try {
        m_IOPort->Open(GetPortName());
        m_Timer->Start(GetInterval());
        m_IsActive = true;
    }
    catch (const Exception &) {
        Stop();
        throw;
    }
}

void BorisController::Stop() {
    if (m_Timer->IsRunning()) {
        m_Timer->Stop();
    }
    if (m_IOPort->IsOpen()) {
        m_IOPort->Close();
    }
    m_IsActive = false;
}

BorisController::~BorisController() {
    try {
        Stop();
    }
    catch (...) {
    }
}
