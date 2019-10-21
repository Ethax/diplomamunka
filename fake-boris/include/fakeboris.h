#ifndef FAKEBORIS_H
#define FAKEBORIS_H

#include <QIODevice>
#include <QObject>

namespace diplomamunka {

class FakeBoris : public QObject {
    Q_OBJECT
public:
    explicit FakeBoris(QIODevice &device, QObject *parent = nullptr);

    void setOutput(int output) noexcept;
    int output() const noexcept;
    void setInput(int input) noexcept;
    int input() const noexcept;

    virtual ~FakeBoris() = default;

signals:
    void outputChanged();
    void inputChanged();

private slots:
    void onReadyRead();

private:
    QIODevice &m_ioDevice;
    int m_output = 0;
    int m_input = 0;
};

} // namespace diplomamunka

#endif // FAKEBORIS_H
