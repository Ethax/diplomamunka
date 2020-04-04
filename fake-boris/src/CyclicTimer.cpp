#include <CyclicTimer.h>
#include <Exception.h>
#include <QThread>

using namespace Diplomamunka;

CyclicTimer::CyclicTimer(QObject* parent) : Timer(parent) {
    connect(&m_timerImpl, &QTimer::timeout, this, &CyclicTimer::elapsed);
}

void CyclicTimer::start(int interval) {
    verifyCanBeStarted(interval);

    m_timerImpl.start(interval);

    verifyStarted();
}

bool CyclicTimer::isRunning() const {
    return m_timerImpl.isActive();
}

void CyclicTimer::stop() {
    verifyCanBeStopped();

    m_timerImpl.stop();
}

TimerPtr CyclicTimer::create() {
    return std::make_shared<CyclicTimer>();
}

void CyclicTimer::verifyCanBeStarted(int interval) {
    if (m_timerImpl.isActive()) {
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

void CyclicTimer::verifyStarted() {
    if (m_timerImpl.timerId() == InvalidTimerId) {
        throw OutOfMemoryException(tr("Failed to start timer."));
    }
}

void CyclicTimer::verifyCanBeStopped() {
    if (!m_timerImpl.isActive()) {
        throw InvalidOperationException(tr("Timer is not running."));
    }

    if (thread() != QThread::currentThread()) {
        throw InvalidOperationException(tr("Timers cannot be stopped from another thread."));
    }
}
