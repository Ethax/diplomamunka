#include <QtCore>
#include <boris_controller.h>
#include <type_traits>

using namespace diplomamunka;

bool BorisController::beginTransaction(const QString &deviceName) {
    if (m_Connection.connect(deviceName)) {
        startScheduler();
        return isActive();
    }
    return false;
}

void BorisController::endTransaction() {
    m_Connection.disconnect();
    stopScheduler();
}

BorisController::BorisController(ConnectionProvider &connection, QObject *parent)
    : QObject(parent), m_Connection(connection) {}

BorisController::~BorisController() { endTransaction(); }

void BorisController::setOutput(int output) noexcept {
    if (m_output != output) {
        m_output = output;
        emit outputChanged();
    }
}

void BorisController::setInterval(int interval) noexcept {
    if (m_interval != interval) {
        m_interval = interval;
        emit intervalChanged();
    }
}

void BorisController::startScheduler() {
    stopScheduler();
    m_TimerId = startTimer(interval());
}

void BorisController::stopScheduler() {
    if (isActive()) {
        killTimer(m_TimerId);
        m_TimerId = InvalidTimerId;
    }
}

void BorisController::timerEvent(QTimerEvent *event) {
    if (event->timerId() == m_TimerId) {
        writeOutput();
    }
}

void BorisController::writeOutput() {
    QByteArray output;

    output.append(WriteCommand);
    output.append(static_cast<char>((m_output >> 8) & 0xff));
    output.append(static_cast<char>(m_output & 0xff));
    output.append(ReadCommand);

    m_Connection.connection().write(output);
}
