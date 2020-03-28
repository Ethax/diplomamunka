#ifndef BASICPORT_H
#define BASICPORT_H

#include <IOPort.hpp>

namespace Diplomamunka {

class BasicPort : public IOPort {
    Q_OBJECT

    virtual void OpenPort(const QString& portName) = 0;
    virtual QByteArray ReadData() = 0;
    virtual void WriteData(const QByteArray& data) = 0;

public:
    explicit BasicPort(QObject* parent = nullptr);

    void Open(const QString& portName) final;
    bool IsOpen() const final;
    void Close() final;
    QByteArray Read() final;
    void Write(const QByteArray& data) final;

    virtual ~BasicPort() override;

private:
    void CloseIfOpen();

    bool m_IsOpen = false;
};

} // namespace Diplomamunka

#endif // BASICPORT_H
