#include <BorisController.h>
#include <CyclicTimer.h>
#include <Exception.h>
#include <SerialPort.h>

using namespace Diplomamunka;

BorisController::BorisController(QObject* parent)
    : BorisController(SerialPort::Create(), CyclicTimer::Create(), parent) {
}

BorisController::BorisController(IOPortPtr ioPort, TimerPtr timer, QObject* parent)
    : QObject(parent), m_IOPort(ioPort), m_Timer(timer) {
    if (ioPort == nullptr) {
        throw ArgumentNullException(tr("Argument 'ioPort' cannot be nullptr."));
    }

    if (timer == nullptr) {
        throw ArgumentNullException(tr("Argument 'timer' cannot be nullptr."));
    }

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
    try {
        StopIfActive();
    }
    catch (...) {
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
    outputData += WriteCommand;
    outputData += static_cast<char>((output >> 8) & 0xff);
    outputData += static_cast<char>(output & 0xff);
    outputData += ReadCommand;

    m_IOPort->Write(outputData);
}

void BorisController::StopIfActive() {
    if (IsActive()) {
        Stop();
    }
}
