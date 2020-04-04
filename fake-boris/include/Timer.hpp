#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <memory>

namespace Diplomamunka {

class Timer : public QObject {
    Q_OBJECT

public:
    explicit Timer(QObject* parent = nullptr) : QObject(parent) {
    }

    virtual void start(int interval) = 0;
    virtual bool isRunning() const = 0;
    virtual void stop() = 0;

signals:
    void elapsed();
};

using TimerPtr = std::shared_ptr<Timer>;

} // namespace Diplomamunka

#endif // TIMER_H
