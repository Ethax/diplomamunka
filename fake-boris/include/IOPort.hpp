#ifndef IOPORT_H
#define IOPORT_H

#include <QByteArray>
#include <QObject>
#include <QStringList>
#include <memory>

namespace Diplomamunka {

class IOPort : public QObject {
    Q_OBJECT

public:
    explicit IOPort(QObject* parent = nullptr) : QObject(parent) {
    }

    virtual QStringList getPortNames() const = 0;
    virtual void open(const QString& portName) = 0;
    virtual bool isOpen() const = 0;
    virtual void close() = 0;
    virtual QByteArray read() = 0;
    virtual void write(const QByteArray& data) = 0;

signals:
    void dataReceived();
};

using IOPortPtr = std::shared_ptr<IOPort>;

} // namespace Diplomamunka

#endif // IOPORT_H
