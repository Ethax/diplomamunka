#include <CyclicTimer.h>
#include <Exception.h>
#include <QThread>

using namespace Diplomamunka;

void Diplomamunka::CyclicTimer::Start(int interval) {
    VerifyCanBeStarted(interval);

    m_TimerImpl.start(interval);

    VerifyStarted();
}

bool Diplomamunka::CyclicTimer::IsRunning() const {
    return m_TimerImpl.isActive();
}

void Diplomamunka::CyclicTimer::Stop() {
    VerifyCanBeStopped();

    m_TimerImpl.stop();
}

TimerPtr CyclicTimer::Create() {
    return std::make_shared<CyclicTimer>();
}

void CyclicTimer::VerifyCanBeStarted(int interval) {
    if (interval < 0) {
        throw ArgumentOutOfRangeException(tr("Timers cannot have negative intervals."));
    }

    if (thread() == nullptr || thread()->eventDispatcher() == nullptr) {
        throw InvalidOperationException(tr("Timers can only be used with event dispatchers."));
    }

    if (thread() != QThread::currentThread()) {
        throw InvalidOperationException(tr("Timers cannot be started from another thread."));
    }
}

void CyclicTimer::VerifyStarted() {
    if (m_TimerImpl.timerId() == InvalidTimerId) {
        throw InvalidOperationException(tr("Failed to start timer."));
    }
}

void CyclicTimer::VerifyCanBeStopped() {
    if (thread() != QThread::currentThread()) {
        throw InvalidOperationException(tr("Timers cannot be stopped from another thread"));
    }

    if (!m_TimerImpl.isActive()) {
        throw InvalidOperationException(tr("Timer is not running."));
    }
}
