#include <Exception.h>

using namespace Diplomamunka;

Exception::Exception(const QString &message) : std::exception(), m_Message(message) {}

QString Exception::GetMessage() const noexcept { return m_Message; }

const char *Exception::what() const noexcept { return m_Message.toUtf8().constData(); }

UnauthorizedAccessException::UnauthorizedAccessException(const QString &message)
    : Exception(message) {}

ArgumentOutOfRangeException::ArgumentOutOfRangeException(const QString &message)
    : Exception(message) {}

IOException::IOException(const QString &message) : Exception(message) {}

InvalidOperationException::InvalidOperationException(const QString &message) : Exception(message) {}

ArgumentNullException::ArgumentNullException(const QString &message) : Exception(message) {}
