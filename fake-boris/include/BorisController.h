#ifndef ABSTRACTBORISCONTROLLER_H
#define ABSTRACTBORISCONTROLLER_H

#include <IOPort.hpp>
#include <PropertyHelper.hpp>
#include <Timer.hpp>

namespace Diplomamunka {

class BorisController : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(BorisController)

    AUTOMATIC_PROPERTY(int, interval) = 10;
    AUTOMATIC_PROPERTY(QString, portName) = "";
    READONLY_PROPERTY(quint16, input) = 0;
    AUTOMATIC_PROPERTY(quint16, output) = 0;

public:
    explicit BorisController(QObject* parent = nullptr);
    explicit BorisController(IOPortPtr ioPort, TimerPtr timer, QObject* parent = nullptr);

    Q_INVOKABLE void start();
    Q_INVOKABLE bool isActive() const;
    Q_INVOKABLE void stop();

    Q_INVOKABLE QStringList getPortNames() const;

    virtual ~BorisController() override;

private slots:
    void readInput();
    void writeOutput();

private:
    void stopIfActive();

    IOPortPtr m_ioPort;
    TimerPtr m_timer;
    bool m_isActive = false;

    static constexpr char ReadCommand = '\xb9';
    static constexpr char WriteCommand = '\xba';
};

} // namespace Diplomamunka

#endif // ABSTRACTBORISCONTROLLER_H
