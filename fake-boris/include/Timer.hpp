#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <memory>

namespace Diplomamunka {

class Timer : public QObject {
    Q_OBJECT

public:
    explicit Timer(QObject *parent = nullptr) : QObject(parent) {}

    virtual void Start(int duration) = 0;
    virtual bool IsRunning() const = 0;
    virtual void Stop() = 0;

signals:
    void Elapsed();
};

using TimerPtr = std::shared_ptr<Timer>;

} // namespace Diplomamunka

#endif // TIMER_H
