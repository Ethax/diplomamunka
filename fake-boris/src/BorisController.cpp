#include <BorisController.h>
#include <Exception.h>

using namespace Diplomamunka;

namespace {

template <typename T> void VerifyNotNullptr(const std::shared_ptr<T> &ptr, const QString &name) {
    if (ptr == nullptr) {
        const auto message = BorisController::tr("Argument '%1' cannot be nullptr.").arg(name);
        throw ArgumentNullException(message);
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
    m_IOPort->Open(GetPortName());
    m_Timer->Start(GetInterval());
    m_IsActive = true;
}

bool BorisController::IsActive() const { return m_IsActive; }

void BorisController::Stop() {
    m_Timer->Stop();
    m_IOPort->Close();
    m_IsActive = false;
}

BorisController::~BorisController() {
    try {
        Stop();
    }
    catch (...) {
    }
}
