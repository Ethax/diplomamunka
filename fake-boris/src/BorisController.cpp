#include <BorisController.h>
#include <CyclicTimer.h>
#include <Exception.h>
#include <SerialPort.h>

using namespace Diplomamunka;

BorisController::BorisController(QObject* parent)
    : BorisController(SerialPort::create(), CyclicTimer::create(), parent) {
}

BorisController::BorisController(IOPortPtr ioPort, TimerPtr timer, QObject* parent)
    : QObject(parent), m_ioPort(ioPort), m_timer(timer) {
    if (ioPort == nullptr) {
        throw ArgumentNullException(tr("Argument 'ioPort' cannot be nullptr."));
    }

    if (timer == nullptr) {
        throw ArgumentNullException(tr("Argument 'timer' cannot be nullptr."));
    }

    connect(m_timer.get(), &Timer::elapsed, this, &BorisController::writeOutput);
    connect(m_ioPort.get(), &IOPort::dataReceived, this, &BorisController::readInput);
}

bool BorisController::start() {
    try {
        m_ioPort->open(portName());
        m_timer->start(interval());
        m_isActive = true;
    }
    catch (const Exception& error) {
        emit errorOccurred(error.getMessage());
    }
    return isActive();
}

bool BorisController::isActive() const {
    return m_isActive;
}

void BorisController::stop() {
    try {
        m_timer->stop();
        m_ioPort->close();
        m_isActive = false;
    }
    catch (const Exception& error) {
        emit errorOccurred(error.getMessage());
    }
}

QStringList BorisController::getPortNames() const {
    return m_ioPort->getPortNames();
}

BorisController::~BorisController() {
    try {
        stopIfActive();
    }
    catch (...) {
    }
}

void BorisController::readInput() {
    const QByteArray readBytes = m_ioPort->read();

    if (readBytes.length() == 2) {
        quint16 newInput = 0;
        newInput |= static_cast<unsigned char>(readBytes[0]) << 8;
        newInput |= static_cast<unsigned char>(readBytes[1]);

        input(newInput);
    }
}

void BorisController::writeOutput() {
    const quint16 newOutput = output();

    QByteArray bytesToWrite;
    bytesToWrite += WriteCommand;
    bytesToWrite += static_cast<char>((newOutput >> 8) & 0xff);
    bytesToWrite += static_cast<char>(newOutput & 0xff);
    bytesToWrite += ReadCommand;

    m_ioPort->write(bytesToWrite);
}

void BorisController::stopIfActive() {
    if (isActive()) {
        stop();
    }
}
