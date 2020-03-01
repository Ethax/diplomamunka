#ifndef VERIFY_HPP
#define VERIFY_HPP

#include <Exception.h>
#include <QObject>
#include <QString>
#include <memory>

namespace Diplomamunka::Verify {

template <typename T> void NotNullptr(const std::shared_ptr<T> &pointer, const QString &name) {
    if (pointer == nullptr) {
        const auto message = QObject::tr("Argument '%1' cannot be nullptr.").arg(name);
        throw ArgumentNullException(message);
    }
}

} // namespace Diplomamunka::Verify

#define VERIFY_NOT_NULLPTR(pointer) Diplomamunka::Verify::NotNullptr(pointer, #pointer)

#endif // VERIFY_HPP
