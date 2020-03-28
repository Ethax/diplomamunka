#include <BasicPort.h>
#include <Exception.h>

using namespace Diplomamunka;

BasicPort::BasicPort(QObject* parent) : IOPort(parent) {
}

void BasicPort::Open(const QString& portName) {
    if (IsOpen()) {
        throw InvalidOperationException(tr("Port is already open."));
    }

    if (!GetPortNames().contains(portName)) {
        throw ArgumentException(tr("Invalid port name was specified."));
    }

    OpenPort(portName);
    m_IsOpen = true;
}

bool BasicPort::IsOpen() const {
    return m_IsOpen;
}

void BasicPort::Close() {
    if (!IsOpen()) {
        throw InvalidOperationException(tr("Port is not open."));
    }

    m_IsOpen = false;
}

QByteArray BasicPort::Read() {
    if (!IsOpen()) {
        throw IOException(tr("Error reading from port."));
    }

    return ReadData();
}

void BasicPort::Write(const QByteArray& data) {
    if (!IsOpen()) {
        throw IOException(tr("Error writing to port."));
    }

    WriteData(data);
}

BasicPort::~BasicPort() {
    try {
        CloseIfOpen();
    }
    catch (...) {
    }
}

void BasicPort::CloseIfOpen() {
    if (IsOpen()) {
        Close();
    }
}
