#include <boris_controller.h>

using namespace diplomamunka;

BorisController::BorisController(ConnectionProvider &connection, QObject *parent)
    : QObject(parent), m_Connection(connection) {
    connect(&m_Connection.connection(), &QIODevice::readyRead, this, &BorisController::onReadyRead);
}

int BorisController::input() const noexcept { return m_input; }

int BorisController::output() const noexcept { return m_output; }

void BorisController::setOutput(int output) noexcept {
    if (m_output != output) {
        m_output = output;
        emit outputChanged();
    }
}

void BorisController::setInput(int input) noexcept {
    if (m_input != input) {
        m_input = input;
        emit inputChanged();
    }
}

void BorisController::onReadyRead() {
    const auto inputBytes = m_Connection.connection().readAll();
    if (inputBytes.length() != 2) {
        return;
    }

    bool ok;
    setInput(inputBytes.toHex().toInt(&ok, 16));
}
