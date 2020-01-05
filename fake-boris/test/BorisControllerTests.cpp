#include <BorisController.h>
#include <QCoreApplication>
#include <QtTest>
#include <fakeit.hpp>

using namespace Diplomamunka;

namespace {

class TestableBorisController : public AbstractBorisController {
    Q_OBJECT

public:
    TestableBorisController() : AbstractBorisController() {}
};

} // namespace

class BorisControllerTests : public QObject {
    Q_OBJECT

private slots:
    void test_case1() {}
};

QTEST_MAIN(BorisControllerTests)

#include "BorisControllerTests.moc"
