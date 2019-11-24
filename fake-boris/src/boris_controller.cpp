#include <QtCore>
#include <boris_controller.h>

using namespace diplomamunka;

BorisController::BorisController(ConnectionProvider &connection, QObject *parent)
    : QObject(parent), m_Connection(connection) {}

void BorisController::setOutput(int output) noexcept {
    if (m_output != output) {
        m_output = output;
        emit outputChanged();
    }
}

bool BorisController::beginTransaction(const QString &deviceName) {
    if (m_Connection.connect(deviceName)) {
        m_TimerId = startTimer(10);
        return m_TimerId != 0;
    }
    return false;
}

void BorisController::writeOutput() {
    QByteArray output;
    output.append(static_cast<char>((m_output >> 8) & 0xff));
    output.append(static_cast<char>(m_output & 0xff));
    m_Connection.connection().write(output);
}

void BorisController::timerEvent(QTimerEvent *event) {
    if (event->timerId() == m_TimerId) {
        writeOutput();
    }
}
