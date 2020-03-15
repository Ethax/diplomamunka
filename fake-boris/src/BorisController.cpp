#include <BorisController.h>
#include <Verify.hpp>

using namespace Diplomamunka;

BorisController::BorisController(IOPortPtr ioPort, TimerPtr timer, QObject* parent)
    : QObject(parent), m_IOPort(ioPort), m_Timer(timer) {
    VERIFY_NOT_NULLPTR(ioPort);
    VERIFY_NOT_NULLPTR(timer);

    connect(m_Timer.get(), &Timer::Elapsed, this, &BorisController::WriteOutput);
    connect(m_IOPort.get(), &IOPort::DataReceived, this, &BorisController::ReadInput);
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

QStringList BorisController::GetPortNames() const {
    return m_IOPort->GetPortNames();
}

BorisController::~BorisController() {
    if (IsActive()) {
        Stop();
    }
}

void BorisController::ReadInput() {
    const QByteArray inputData = m_IOPort->Read();

    if (inputData.length() == 2) {
        quint16 input = 0;
        input |= static_cast<unsigned char>(inputData[0]) << 8;
        input |= static_cast<unsigned char>(inputData[1]);

        SetInput(input);
    }
}

void BorisController::WriteOutput() {
    const quint16 output = GetOutput();

    QByteArray outputData;
    outputData.append(WriteCommand);
    outputData.append(static_cast<char>((output >> 8) & 0xff));
    outputData.append(static_cast<char>(output & 0xff));
    outputData.append(ReadCommand);

    m_IOPort->Write(outputData);
}
