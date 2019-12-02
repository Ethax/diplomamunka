#ifndef BORIS_CONTROLLER_H
#define BORIS_CONTROLLER_H

#include <QIODevice>
#include <QObject>
#include <QTimer>
#include <connection_provider.h>

namespace diplomamunka {

class BorisController : public QObject {
    Q_OBJECT
    Q_PROPERTY(int output READ output WRITE setOutput NOTIFY outputChanged)
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)

public:
    Q_INVOKABLE bool beginTransaction(const QString &deviceName);
    Q_INVOKABLE bool isActive() const noexcept { return m_TimerId >= 0; }
    Q_INVOKABLE void endTransaction();

    explicit BorisController(ConnectionProvider &connection, QObject *parent = nullptr);
    ~BorisController() override;

    int output() const noexcept { return m_output; }
    int interval() const noexcept { return m_interval; }
    void setOutput(int output) noexcept;
    void setInterval(int interval) noexcept;

signals:
    void outputChanged();
    void intervalChanged();

private:
    void startScheduler();
    void stopScheduler();
    void timerEvent(QTimerEvent *event) override;
    void writeOutput();

    static constexpr int InvalidTimerId = -1;
    static constexpr char WriteCommand = '\xba';
    static constexpr char ReadCommand = '\xb9';

    ConnectionProvider &m_Connection;
    int m_output = 0;
    int m_interval = 0;
    int m_TimerId = InvalidTimerId;
};

} // namespace diplomamunka

#endif // BORIS_CONTROLLER_H
