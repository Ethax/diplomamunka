#include <TestDummy.h>

using namespace Diplomamunka::UnitTest;

QStringList DummyIOPort::GetPortNames() const { return {}; }

void DummyIOPort::Open(const QString &) {}

bool DummyIOPort::IsOpen() const { return {}; }

void DummyIOPort::Close() {}

QByteArray DummyIOPort::Read() { return {}; }

void DummyIOPort::Write(const QByteArray &) {}

void Diplomamunka::UnitTest::DummyTimer::Start(int) {}

bool Diplomamunka::UnitTest::DummyTimer::IsRunning() const { return {}; }

void Diplomamunka::UnitTest::DummyTimer::Stop() {}
