#include <EchoPort.h>

using namespace Diplomamunka;

EchoPort::EchoPort(QObject* parent) : DeveloperPort(parent) {
}

QStringList Diplomamunka::EchoPort::GetPortNames() const {
    return {NormalEcho, InverseEcho};
}

IOPortPtr EchoPort::Create() {
    return std::make_shared<EchoPort>();
}

void Diplomamunka::EchoPort::OpenPort(const QString& portName) {
    m_InverseMode = (portName == InverseEcho);
}

QByteArray Diplomamunka::EchoPort::ReadData() {
    const quint16 data = m_InverseMode ? ~m_Data : m_Data;

    QByteArray output;
    output += static_cast<char>((data >> 8) & 0xff);
    output += static_cast<char>(data & 0xff);

    return output;
}

void Diplomamunka::EchoPort::WriteData(const QByteArray& data) {
    StoreData(data);
    emit DataReceived();
}

void EchoPort::StoreData(const QByteArray& data) {
    const QByteArray payload = data.mid(1, 2);

    if (payload.size() == 2) {
        m_Data = 0;
        m_Data |= static_cast<unsigned char>(payload[0]) << 8;
        m_Data |= static_cast<unsigned char>(payload[1]);
    }
}
