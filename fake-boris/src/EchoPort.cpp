#include <EchoPort.h>
#include <algorithm>

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
    QByteArray data;

    for (auto dataByte : m_Data) {
        data.append(m_InverseMode ? ~dataByte : dataByte);
    }

    return data;
}

void Diplomamunka::EchoPort::WriteData(const QByteArray& data) {
    StoreData(data);
    emit DataReceived();
}

void EchoPort::StoreData(const QByteArray& data) {
    const auto payload = data.mid(1, sizeof(m_Data));

    if (payload.size() == sizeof(m_Data)) {
        std::copy(payload.begin(), payload.end(), std::begin(m_Data));
    }
}
