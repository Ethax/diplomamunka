#ifndef IOEXCEPTION_H
#define IOEXCEPTION_H

#include <QString>
#include <stdexcept>

namespace Diplomamunka {

class Exception : public std::exception {
public:
    explicit Exception(const QString& message);

    QString getMessage() const noexcept;
    const char* what() const noexcept override;

private:
    QString m_message;
};

class ArgumentException : public Exception {
public:
    explicit ArgumentException(const QString& message);
};

class ArgumentNullException : public Exception {
public:
    explicit ArgumentNullException(const QString& message);
};

class ArgumentOutOfRangeException : public Exception {
public:
    explicit ArgumentOutOfRangeException(const QString& message);
};

class InvalidOperationException : public Exception {
public:
    explicit InvalidOperationException(const QString& message);
};

class IOException : public Exception {
public:
    explicit IOException(const QString& message);
};

class OutOfMemoryException : public Exception {
public:
    explicit OutOfMemoryException(const QString& message);
};

class TimeoutException : public Exception {
public:
    explicit TimeoutException(const QString& message);
};

class UnauthorizedAccessException : public Exception {
public:
    explicit UnauthorizedAccessException(const QString& message);
};

} // namespace Diplomamunka

#endif // IOEXCEPTION_H
