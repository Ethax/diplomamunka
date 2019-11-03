#ifndef CONNECTION_PROVIDER_H
#define CONNECTION_PROVIDER_H

#include <QIODevice>

namespace diplomamunka {

class ConnectionProvider {
public:
    virtual QIODevice &connection() = 0;
    virtual bool open(const QString &portName) = 0;
    virtual void close() = 0;
    virtual ~ConnectionProvider() = default;
};

} // namespace diplomamunka

#endif // CONNECTION_PROVIDER_H
