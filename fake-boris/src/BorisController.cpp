#include <BorisController.h>

using namespace Diplomamunka;

AbstractBorisController::AbstractBorisController(QObject *parent) : QObject(parent) {}

BorisController::BorisController(QObject *parent) : AbstractBorisController(parent) {}
