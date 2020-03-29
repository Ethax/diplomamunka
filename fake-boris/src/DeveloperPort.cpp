#include <DeveloperPort.h>
#include <Exception.h>

using namespace Diplomamunka;

DeveloperPort::DeveloperPort(QObject* parent) : IOPort(parent) {
}

void DeveloperPort::Open(const QString& portName) {
    if (IsOpen()) {
        throw InvalidOperationException(tr("Port is already open."));
    }

    if (!GetPortNames().contains(portName)) {
        throw ArgumentException(tr("Invalid port name was specified."));
    }

    OpenPort(portName);
    m_IsOpen = true;
}

bool DeveloperPort::IsOpen() const {
    return m_IsOpen;
}

void DeveloperPort::Close() {
    if (!IsOpen()) {
        throw InvalidOperationException(tr("Port is not open."));
    }

    m_IsOpen = false;
}

QByteArray DeveloperPort::Read() {
    if (!IsOpen()) {
        throw IOException(tr("Error reading from port."));
    }

    return ReadData();
}

void DeveloperPort::Write(const QByteArray& data) {
    if (!IsOpen()) {
        throw IOException(tr("Error writing to port."));
    }

    WriteData(data);
}
