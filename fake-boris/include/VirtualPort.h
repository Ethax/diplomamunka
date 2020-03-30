#ifndef VIRTUALPORT_H
#define VIRTUALPORT_H

#include <DeveloperPort.h>
#include <PropertyHelper.hpp>

namespace Diplomamunka {

class VirtualPort final : public DeveloperPort {
    Q_OBJECT
    Q_DISABLE_COPY(VirtualPort)

    AUTOMATIC_PROPERTY(quint16, Data) = 0;

public:
    explicit VirtualPort(QObject* parent = nullptr);

    QStringList GetPortNames() const override;

    static IOPortPtr Create();

private:
    void OpenPort(const QString&) override;
    QByteArray ReadData() override;
    void WriteData(const QByteArray&) override;

    static constexpr const char* Port = "VIRTUAL";
};

} // namespace Diplomamunka

#endif // VIRTUALPORT_H
