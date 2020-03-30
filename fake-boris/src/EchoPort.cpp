#include <EchoPort.h>
#include <algorithm>
#include <numeric>

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

    for (auto item : m_Data) {
        data.append(m_InverseMode ? ~item : item);
    }

    return data;
}

void Diplomamunka::EchoPort::WriteData(const QByteArray& data) {
    StoreData(data);
    emit DataReceived();
}

void EchoPort::StoreData(const QByteArray& data) {
    const auto payload = data.mid(1, sizeof(m_Data));

    if (payload.size() != sizeof(m_Data)) {
        return;
    }

    for (int i = 0; i < payload.size(); ++i) {
        m_Data[i] = payload[i];
    }
}
