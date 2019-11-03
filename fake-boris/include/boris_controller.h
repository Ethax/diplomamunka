#ifndef BORIS_CONTROLLER_H
#define BORIS_CONTROLLER_H

#include <QIODevice>
#include <QObject>
#include <connection_provider.h>

namespace diplomamunka {

class BorisController : public QObject {
    Q_OBJECT

public:
    explicit BorisController(ConnectionProvider &connection, QObject *parent = nullptr);

    int input() const noexcept;
    int output() const noexcept;
    void setOutput(int output) noexcept;

signals:
    void outputChanged();
    void inputChanged();

protected:
    void setInput(int input) noexcept;

    int m_input = 0;
    int m_output = 0;

private slots:
    void onReadyRead();

private:
    ConnectionProvider &m_Connection;
};

} // namespace diplomamunka

#endif // BORIS_CONTROLLER_H
