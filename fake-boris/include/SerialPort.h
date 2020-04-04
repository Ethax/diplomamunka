#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <IOPort.hpp>
#include <QSerialPort>

namespace Diplomamunka {

class SerialPort final : public IOPort {
    Q_OBJECT
    Q_DISABLE_COPY(SerialPort)

public:
    explicit SerialPort(QObject* parent = nullptr);

    QStringList getPortNames() const override;
    void open(const QString& portName) override;
    bool isOpen() const override;
    void close() override;
    QByteArray read() override;
    void write(const QByteArray& data) override;

    static IOPortPtr create();

private:
    void verifyNoErrors();

    QSerialPort m_portImpl;
};

} // namespace Diplomamunka

#endif // SERIALPORT_H
