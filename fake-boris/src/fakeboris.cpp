#include <fakeboris.h>

using namespace diplomamunka;

FakeBoris::FakeBoris(QIODevice &device, QObject *parent) : QObject(parent), m_ioDevice(device) {
    connect(&m_ioDevice, &QIODevice::readyRead, this, &FakeBoris::onReadyRead);
}

void FakeBoris::setOutput(int output) noexcept {
    if (m_output != output) {
        m_output = output;
        emit outputChanged();
    }
}

int FakeBoris::output() const noexcept { return m_output; }

void FakeBoris::setInput(int input) noexcept {
    if (m_input != input) {
        m_input = input;
        emit inputChanged();
    }
}

int FakeBoris::input() const noexcept { return m_input; }

void FakeBoris::onReadyRead() {
    const auto inputBytes = m_ioDevice.readAll();
    if (inputBytes.length() != 2) {
        return;
    }

    bool ok;
    setInput(inputBytes.toHex().toInt(&ok, 16));
}
