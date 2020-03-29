#ifndef DEVELOPERPORT_H
#define DEVELOPERPORT_H

#include <IOPort.hpp>

namespace Diplomamunka {

class DeveloperPort : public IOPort {
    Q_OBJECT

    virtual void OpenPort(const QString& portName) = 0;
    virtual QByteArray ReadData() = 0;
    virtual void WriteData(const QByteArray& data) = 0;

public:
    explicit DeveloperPort(QObject* parent = nullptr);

    void Open(const QString& portName) final;
    bool IsOpen() const final;
    void Close() final;
    QByteArray Read() final;
    void Write(const QByteArray& data) final;

private:
    bool m_IsOpen = false;
};

} // namespace Diplomamunka

#endif // DEVELOPERPORT_H
