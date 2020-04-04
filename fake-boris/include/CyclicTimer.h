#ifndef REPETITIVETIMER_H
#define REPETITIVETIMER_H

#include <QTimer>
#include <Timer.hpp>

namespace Diplomamunka {

class CyclicTimer final : public Timer {
    Q_OBJECT
    Q_DISABLE_COPY(CyclicTimer)

public:
    explicit CyclicTimer(QObject* parent = nullptr);

    void start(int interval) override;
    bool isRunning() const override;
    void stop() override;

    static TimerPtr create();

private:
    void verifyCanBeStarted(int interval);
    void verifyStarted();
    void verifyCanBeStopped();

    QTimer m_timerImpl;

    static constexpr int InvalidTimerId = -1;
};

} // namespace Diplomamunka

#endif // REPETITIVETIMER_H
