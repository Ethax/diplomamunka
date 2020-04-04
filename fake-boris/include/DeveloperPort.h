#ifndef DEVELOPERPORT_H
#define DEVELOPERPORT_H

#include <IOPort.hpp>

namespace Diplomamunka {

class DeveloperPort : public IOPort {
    Q_OBJECT

    virtual void openPort(const QString& portName) = 0;
    virtual QByteArray readData() = 0;
    virtual void writeData(const QByteArray& data) = 0;

public:
    explicit DeveloperPort(QObject* parent = nullptr);

    void open(const QString& portName) final;
    bool isOpen() const final;
    void close() final;
    QByteArray read() final;
    void write(const QByteArray& data) final;

private:
    bool m_isOpen = false;
};

} // namespace Diplomamunka

#endif // DEVELOPERPORT_H
