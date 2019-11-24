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

public:
    explicit BorisController(ConnectionProvider &connection, QObject *parent = nullptr);
    bool beginTransaction(const QString &deviceName);

    int output() const noexcept { return m_output; }
    void setOutput(int output) noexcept;

signals:
    void outputChanged();

protected:
    QTimer m_CommunicationScheduler;

private:
    void writeOutput();

    ConnectionProvider &m_Connection;
    int m_output = 0;
    // QObject interface
protected:
    void timerEvent(QTimerEvent *event) override;
    int m_TimerId = 0;
};

} // namespace diplomamunka

#endif // BORIS_CONTROLLER_H
