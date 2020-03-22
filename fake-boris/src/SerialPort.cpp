#include <Exception.h>
#include <QSerialPortInfo>
#include <SerialPort.h>

using namespace Diplomamunka;

SerialPort::SerialPort(QObject* parent) : IOPort(parent) {
    connect(&m_PortImpl, &QSerialPort::readyRead, this, &SerialPort::DataReceived);
}

QStringList Diplomamunka::SerialPort::GetPortNames() const {
    QStringList portNames;

    for (const auto& port : QSerialPortInfo::availablePorts()) {
        portNames << port.portName();
    }

    return portNames;
}

void Diplomamunka::SerialPort::Open(const QString& portName) {
    m_PortImpl.setPortName(portName);
    m_PortImpl.open(QSerialPort::ReadWrite);

    VerifyNoErrors();
}

bool Diplomamunka::SerialPort::IsOpen() const {
    return m_PortImpl.isOpen();
}

void Diplomamunka::SerialPort::Close() {
    m_PortImpl.close();

    VerifyNoErrors();
}

QByteArray Diplomamunka::SerialPort::Read() {
    const auto receivedData = m_PortImpl.readAll();

    VerifyNoErrors();

    return receivedData;
}

void Diplomamunka::SerialPort::Write(const QByteArray& data) {
    m_PortImpl.write(data);

    VerifyNoErrors();
}

IOPortPtr SerialPort::Create() {
    return std::make_shared<SerialPort>();
}

void SerialPort::VerifyNoErrors() {
    const auto errorMessage = m_PortImpl.errorString();

    switch (m_PortImpl.error()) {
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
