#include <EchoPort.h>

using namespace Diplomamunka;

EchoPort::EchoPort(QObject* parent) : DeveloperPort(parent) {
}

QStringList EchoPort::getPortNames() const {
    return {NormalEcho, InverseEcho};
}

IOPortPtr EchoPort::create() {
    return std::make_shared<EchoPort>();
}

void EchoPort::openPort(const QString& portName) {
    m_inverseMode = (portName == InverseEcho);
}

QByteArray EchoPort::readData() {
    const quint16 data = m_inverseMode ? ~m_data : m_data;

    QByteArray output;
    output += static_cast<char>((data >> 8) & 0xff);
    output += static_cast<char>(data & 0xff);

    return output;
}

void EchoPort::writeData(const QByteArray& data) {
    storeData(data);
    emit dataReceived();
}

void EchoPort::storeData(const QByteArray& data) {
    const QByteArray payload = data.mid(1, 2);

    if (payload.size() == 2) {
        m_data = 0;
        m_data |= static_cast<unsigned char>(payload[0]) << 8;
        m_data |= static_cast<unsigned char>(payload[1]);
    }
}
