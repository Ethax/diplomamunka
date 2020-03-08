#include <BorisController.h>
#include <Verify.hpp>

using namespace Diplomamunka;

BorisController::BorisController(IOPortPtr ioPort, TimerPtr timer, QObject* parent)
    : QObject(parent), m_IOPort(ioPort), m_Timer(timer) {
    VERIFY_NOT_NULLPTR(ioPort);
    VERIFY_NOT_NULLPTR(timer);

    connect(m_Timer.get(), &Timer::Elapsed, this, &BorisController::WriteOutput);
}

void BorisController::Start() {
    m_IOPort->Open(GetPortName());
    m_Timer->Start(GetInterval());
    m_IsActive = true;
}

bool BorisController::IsActive() const {
    return m_IsActive;
}

void BorisController::Stop() {
    m_Timer->Stop();
    m_IOPort->Close();
    m_IsActive = false;
}

BorisController::~BorisController() {
    if (IsActive()) {
        Stop();
    }
}

void BorisController::WriteOutput() {
    QByteArray output;

    output.append(WriteCommand);
    output.append(static_cast<char>((GetOutput() >> 8) & 0xff));
    output.append(static_cast<char>(GetOutput() & 0xff));
    output.append(ReadCommand);

    m_IOPort->Write(output);
}
