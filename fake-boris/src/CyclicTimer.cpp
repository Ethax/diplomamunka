#include <CyclicTimer.h>
#include <Exception.h>
#include <QThread>

using namespace Diplomamunka;

CyclicTimer::CyclicTimer(QObject* parent) : Timer(parent) {
    connect(&m_TimerImpl, &QTimer::timeout, this, &CyclicTimer::Elapsed);
}

void CyclicTimer::Start(int interval) {
    VerifyCanBeStarted(interval);

    m_TimerImpl.start(interval);

    VerifyStarted();
}

bool CyclicTimer::IsRunning() const {
    return m_TimerImpl.isActive();
}

void CyclicTimer::Stop() {
    VerifyCanBeStopped();

    m_TimerImpl.stop();
}

TimerPtr CyclicTimer::Create() {
    return std::make_shared<CyclicTimer>();
}

void CyclicTimer::VerifyCanBeStarted(int interval) {
    if (m_TimerImpl.isActive()) {
        throw InvalidOperationException(tr("Timer is already running."));
    }

    if (interval < 0) {
        throw ArgumentOutOfRangeException(tr("Timers cannot have negative intervals."));
    }

    if (thread()->eventDispatcher() == nullptr) {
        throw InvalidOperationException(tr("Timers cannot be used without event dispatchers."));
    }

    if (thread() != QThread::currentThread()) {
        throw InvalidOperationException(tr("Timers cannot be started from another thread."));
    }
}

void CyclicTimer::VerifyStarted() {
    if (m_TimerImpl.timerId() == InvalidTimerId) {
        throw OutOfMemoryException(tr("Failed to start timer."));
    }
}

void CyclicTimer::VerifyCanBeStopped() {
    if (!m_TimerImpl.isActive()) {
        throw InvalidOperationException(tr("Timer is not running."));
    }

    if (thread() != QThread::currentThread()) {
        throw InvalidOperationException(tr("Timers cannot be stopped from another thread"));
    }
}
