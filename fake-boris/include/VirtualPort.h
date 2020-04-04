#ifndef VIRTUALPORT_H
#define VIRTUALPORT_H

#include <DeveloperPort.h>
#include <PropertyHelper.hpp>

namespace Diplomamunka {

class VirtualPort final : public DeveloperPort {
    Q_OBJECT
    Q_DISABLE_COPY(VirtualPort)

    AUTOMATIC_PROPERTY(quint16, data) = 0;

public:
    explicit VirtualPort(QObject* parent = nullptr);

    QStringList getPortNames() const override;

    static IOPortPtr create();

private:
    void openPort(const QString&) override;
    QByteArray readData() override;
    void writeData(const QByteArray&) override;

    static constexpr const char* Port = "VIRTUAL";
};

} // namespace Diplomamunka

#endif // VIRTUALPORT_H
