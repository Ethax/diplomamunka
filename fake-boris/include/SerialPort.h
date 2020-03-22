#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <IOPort.hpp>
#include <QSerialPort>

namespace Diplomamunka {

class SerialPort : public IOPort {
    Q_OBJECT
    Q_DISABLE_COPY(SerialPort)

public:
    explicit SerialPort(QObject* parent = nullptr);

    QStringList GetPortNames() const override;
    void Open(const QString& portName) override;
    bool IsOpen() const override;
    void Close() override;
    QByteArray Read() override;
    void Write(const QByteArray& data) override;

    static IOPortPtr Create();

private:
    void VerifyNoErrors();

    QSerialPort m_PortImpl;
};

} // namespace Diplomamunka

#endif // SERIALPORT_H
