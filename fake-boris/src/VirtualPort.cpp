#include <VirtualPort.h>

using namespace Diplomamunka;

VirtualPort::VirtualPort(QObject* parent) : DeveloperPort(parent) {
}

QStringList VirtualPort::getPortNames() const {
    return {Port};
}

IOPortPtr VirtualPort::create() {
    return std::make_shared<VirtualPort>();
}

void VirtualPort::openPort(const QString&) {
}

QByteArray VirtualPort::readData() {
    QByteArray output;
    output += static_cast<char>((data() >> 8) & 0xff);
    output += static_cast<char>(data() & 0xff);

    return output;
}

void VirtualPort::writeData(const QByteArray&) {
    emit dataReceived();
}
