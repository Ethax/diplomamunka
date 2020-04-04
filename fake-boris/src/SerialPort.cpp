#include <Exception.h>
#include <QSerialPortInfo>
#include <SerialPort.h>

using namespace Diplomamunka;

SerialPort::SerialPort(QObject* parent) : IOPort(parent) {
    connect(&m_portImpl, &QSerialPort::readyRead, this, &SerialPort::dataReceived);
}

QStringList SerialPort::getPortNames() const {
    QStringList portNames;

    for (const auto& port : QSerialPortInfo::availablePorts()) {
        portNames << port.portName();
    }

    return portNames;
}

void SerialPort::open(const QString& portName) {
    m_portImpl.setPortName(portName);
    m_portImpl.open(QSerialPort::ReadWrite);

    verifyNoErrors();
}

bool SerialPort::isOpen() const {
    return m_portImpl.isOpen();
}

void SerialPort::close() {
    m_portImpl.close();

    verifyNoErrors();
}

QByteArray SerialPort::read() {
    const auto receivedData = m_portImpl.readAll();

    verifyNoErrors();

    return receivedData;
}

void SerialPort::write(const QByteArray& data) {
    m_portImpl.write(data);

    verifyNoErrors();
}

IOPortPtr SerialPort::create() {
    return std::make_shared<SerialPort>();
}

void SerialPort::verifyNoErrors() {
    const auto errorMessage = m_portImpl.errorString();

    switch (m_portImpl.error()) {
    case QSerialPort::NoError:
        return;

    case QSerialPort::DeviceNotFoundError:
        throw ArgumentException(errorMessage);

    case QSerialPort::PermissionError:
        throw UnauthorizedAccessException(errorMessage);

    case QSerialPort::OpenError:
    case QSerialPort::NotOpenError:
    case QSerialPort::UnsupportedOperationError:
        throw InvalidOperationException(errorMessage);

    case QSerialPort::TimeoutError:
        throw TimeoutException(errorMessage);

    default:
        throw IOException(errorMessage);
    }
}
