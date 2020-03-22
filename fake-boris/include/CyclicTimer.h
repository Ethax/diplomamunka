#ifndef REPETITIVETIMER_H
#define REPETITIVETIMER_H

#include <QTimer>
#include <Timer.hpp>

namespace Diplomamunka {

class CyclicTimer : public Timer {
    Q_OBJECT
    Q_DISABLE_COPY(CyclicTimer)

public:
    explicit CyclicTimer(QObject* parent = nullptr);

    void Start(int interval) override;
    bool IsRunning() const override;
    void Stop() override;

    static TimerPtr Create();

private:
    void VerifyCanBeStarted(int interval);
    void VerifyStarted();
    void VerifyCanBeStopped();

    QTimer m_TimerImpl;

    static constexpr int InvalidTimerId = -1;
};

} // namespace Diplomamunka

#endif // REPETITIVETIMER_H
