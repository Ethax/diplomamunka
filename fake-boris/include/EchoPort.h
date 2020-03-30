#ifndef ECHOPORT_H
#define ECHOPORT_H

#include <DeveloperPort.h>

namespace Diplomamunka {

class EchoPort final : public DeveloperPort {
    Q_OBJECT
    Q_DISABLE_COPY(EchoPort)

public:
    explicit EchoPort(QObject* parent = nullptr);

    QStringList GetPortNames() const override;

    static IOPortPtr Create();

private:
    void OpenPort(const QString& portName) override;
    QByteArray ReadData() override;
    void WriteData(const QByteArray& data) override;

    void StoreData(const QByteArray& data);

    bool m_InverseMode {};
    char m_Data[2] {};

    static constexpr const char* NormalEcho = "ECHO (NORMAL)";
    static constexpr const char* InverseEcho = "ECHO (INVERSE)";
};

} // namespace Diplomamunka

#endif // ECHOPORT_H
