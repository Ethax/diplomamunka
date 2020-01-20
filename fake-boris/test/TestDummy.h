#ifndef TESTDUMMY_H
#define TESTDUMMY_H

#include <IOPort.hpp>
#include <Timer.hpp>

namespace Diplomamunka::UnitTest {

class DummyIOPort : public Diplomamunka::IOPort {
public:
    QStringList GetPortNames() const override;
    void Open(const QString &) override;
    bool IsOpen() const override;
    void Close() override;
    QByteArray Read() override;
    void Write(const QByteArray &) override;
};

class DummyTimer : public Diplomamunka::Timer {
public:
    void Start(int) override;
    bool IsRunning() const override;
    void Stop() override;
};

} // namespace Diplomamunka::UnitTest

#endif // TESTDUMMY_H
