#ifndef ABSTRACTBORISCONTROLLER_H
#define ABSTRACTBORISCONTROLLER_H

#include <QObject>
#include <property_helper.hpp>

namespace diplomamunka {

class AbstractBorisController : public QObject {
    Q_OBJECT
public:
    explicit AbstractBorisController(QObject *parent = nullptr);

private:
    AUTOMATIC_PROPERTY(int, Interval) = 10;
    AUTOMATIC_PROPERTY(QString, PortName) = "";
    READONLY_PROPERTY(quint16, Input) = 0;
    AUTOMATIC_PROPERTY(quint16, Output) = 0;

    static constexpr char ReadCommand = '\xb9';
    static constexpr char WriteCommand = '\xba';
};

} // namespace diplomamunka

#endif // ABSTRACTBORISCONTROLLER_H
