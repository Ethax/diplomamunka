#ifndef ECHOPORT_H
#define ECHOPORT_H

#include <DeveloperPort.h>

namespace Diplomamunka {

class EchoPort final : public DeveloperPort {
    Q_OBJECT
    Q_DISABLE_COPY(EchoPort)

public:
    explicit EchoPort(QObject* parent = nullptr);

    QStringList getPortNames() const override;

    static IOPortPtr create();

private:
    void openPort(const QString& portName) override;
    QByteArray readData() override;
    void writeData(const QByteArray& data) override;

    void storeData(const QByteArray& data);

    bool m_inverseMode = false;
    quint16 m_data = 0;

    static constexpr const char* NormalEcho = "ECHO (NORMAL)";
    static constexpr const char* InverseEcho = "ECHO (INVERSE)";
};

} // namespace Diplomamunka

#endif // ECHOPORT_H
