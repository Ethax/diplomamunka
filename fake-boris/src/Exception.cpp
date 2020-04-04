#include <Exception.h>

using namespace Diplomamunka;

Exception::Exception(const QString& message) : std::exception(), m_message(message) {
}

QString Exception::getMessage() const noexcept {
    return m_message;
}

const char* Exception::what() const noexcept {
    return m_message.toUtf8().constData();
}

ArgumentException::ArgumentException(const QString& message)
    : Exception(message) {
}

ArgumentNullException::ArgumentNullException(const QString& message)
    : Exception(message) {
}

ArgumentOutOfRangeException::ArgumentOutOfRangeException(const QString& message)
    : Exception(message) {
}

InvalidOperationException::InvalidOperationException(const QString& message)
    : Exception(message) {
}

IOException::IOException(const QString& message)
    : Exception(message) {
}

OutOfMemoryException::OutOfMemoryException(const QString& message)
    : Exception(message) {
}

TimeoutException::TimeoutException(const QString& message)
    : Exception(message) {
}

UnauthorizedAccessException::UnauthorizedAccessException(const QString& message)
    : Exception(message) {
}
