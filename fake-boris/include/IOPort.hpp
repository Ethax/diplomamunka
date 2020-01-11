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
    explicit IOPort(QObject *parent = nullptr) : QObject(parent) {}

    virtual QStringList GetPortNames() const = 0;
    virtual void Open(const QString &portName) = 0;
    virtual bool IsOpen() const = 0;
    virtual void Close() = 0;
    virtual QByteArray Read() = 0;
    virtual void Write(const QByteArray &data) = 0;

signals:
    void DataReceived();
};

using IOPortPtr = std::shared_ptr<IOPort>;

} // namespace Diplomamunka

#endif // IOPORT_H
