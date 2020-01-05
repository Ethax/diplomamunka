#ifndef ABSTRACTBORISCONTROLLER_H
#define ABSTRACTBORISCONTROLLER_H

#include <IOPort.hpp>
#include <PropertyHelper.hpp>
#include <QObject>
#include <Timer.hpp>

namespace Diplomamunka {

class AbstractBorisController : public QObject {
    Q_OBJECT

    AUTOMATIC_PROPERTY(int, Interval) = 10;
    AUTOMATIC_PROPERTY(QString, PortName) = "";
    READONLY_PROPERTY(quint16, Input) = 0;
    AUTOMATIC_PROPERTY(quint16, Output) = 0;

public:
    explicit AbstractBorisController(QObject *parent = nullptr);

    void Start();
    bool IsActive() const;

private:
    virtual IOPort &GetIOPort() = 0;
    virtual Timer &GetTimer() = 0;
    virtual const IOPort &GetIOPort() const = 0;
    virtual const Timer &GetTimer() const = 0;

    static constexpr char ReadCommand = '\xb9';
    static constexpr char WriteCommand = '\xba';
};

class BorisController : public AbstractBorisController {
    Q_OBJECT

public:
    BorisController(QObject *parent = nullptr);
};

} // namespace Diplomamunka

#endif // ABSTRACTBORISCONTROLLER_H
