#include <VirtualPort.h>

using namespace Diplomamunka;

VirtualPort::VirtualPort(QObject* parent) : DeveloperPort(parent) {
}

QStringList VirtualPort::GetPortNames() const {
    return {Port};
}

IOPortPtr VirtualPort::Create() {
    return std::make_shared<VirtualPort>();
}

void VirtualPort::OpenPort(const QString&) {
}

QByteArray VirtualPort::ReadData() {
    QByteArray data;
    data += static_cast<char>((GetData() >> 8) & 0xff);
    data += static_cast<char>(GetData() & 0xff);

    return data;
}

void VirtualPort::WriteData(const QByteArray&) {
    emit DataReceived();
}
