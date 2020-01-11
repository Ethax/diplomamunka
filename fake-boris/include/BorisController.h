#ifndef ABSTRACTBORISCONTROLLER_H
#define ABSTRACTBORISCONTROLLER_H

#include <IOPort.hpp>
#include <PropertyHelper.hpp>
#include <QObject>
#include <Timer.hpp>

namespace Diplomamunka {

class BorisController : public QObject {
    Q_OBJECT

    AUTOMATIC_PROPERTY(int, Interval) = 10;
    AUTOMATIC_PROPERTY(QString, PortName) = "";
    READONLY_PROPERTY(quint16, Input) = 0;
    AUTOMATIC_PROPERTY(quint16, Output) = 0;

public:
    explicit BorisController(QObject *parent = nullptr);
    explicit BorisController(IOPortPtr ioPort, TimerPtr timer, QObject *parent = nullptr);

    Q_INVOKABLE void Start();
    Q_INVOKABLE bool IsActive() const { return m_IsActive; }
    Q_INVOKABLE void Stop();

    virtual ~BorisController() override;

private:
    IOPortPtr m_IOPort;
    TimerPtr m_Timer;
    bool m_IsActive = false;

    static constexpr char ReadCommand = '\xb9';
    static constexpr char WriteCommand = '\xba';
};

} // namespace Diplomamunka

#endif // ABSTRACTBORISCONTROLLER_H
