#include <DeveloperPort.h>
#include <Exception.h>

using namespace Diplomamunka;

DeveloperPort::DeveloperPort(QObject* parent) : IOPort(parent) {
}

void DeveloperPort::open(const QString& portName) {
    if (isOpen()) {
        throw InvalidOperationException(tr("Port is already open."));
    }

    if (!getPortNames().contains(portName)) {
        throw ArgumentException(tr("Invalid port name was specified."));
    }

    openPort(portName);
    m_isOpen = true;
}

bool DeveloperPort::isOpen() const {
    return m_isOpen;
}

void DeveloperPort::close() {
    if (!isOpen()) {
        throw InvalidOperationException(tr("Port is not open."));
    }

    m_isOpen = false;
}

QByteArray DeveloperPort::read() {
    if (!isOpen()) {
        throw IOException(tr("Error reading from port."));
    }

    return readData();
}

void DeveloperPort::write(const QByteArray& data) {
    if (!isOpen()) {
        throw IOException(tr("Error writing to port."));
    }

    writeData(data);
}
