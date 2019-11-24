#ifndef CONNECTION_PROVIDER_H
#define CONNECTION_PROVIDER_H

#include <QIODevice>

namespace diplomamunka {

class ConnectionProvider {
public:
    virtual QIODevice &connection() = 0;
    virtual QStringList availableDevices() const = 0;
    virtual bool connect(const QString &deviceName) = 0;
    virtual void disconnect() = 0;
    virtual ~ConnectionProvider() = default;
};

} // namespace diplomamunka

#endif // CONNECTION_PROVIDER_H
