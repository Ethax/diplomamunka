#include <CyclicTimer.h>
#include <Exception.h>
#include <QSignalSpy>
#include <QtConcurrent/QtConcurrentRun>
#include <future>
#include <gmock/gmock.h>

using namespace testing;
using namespace Diplomamunka;

namespace Diplomamunka::UnitTest {

TEST(CyclicTimerTests, Start_TimerIsAlreadyRunning_ThrowsException) {
    CyclicTimer timer;

    timer.Start(100);

    ASSERT_THROW(timer.Start(200), InvalidOperationException);
}

TEST(CyclicTimerTests, Start_IntervalIsNegative_ThrowsException) {
    CyclicTimer timer;

    ASSERT_THROW(timer.Start(-10), ArgumentOutOfRangeException);
}

TEST(CyclicTimerTests, Start_CalledOnThreadWithoutEventDispatcher_ThrowsException) {
    auto result = std::async(std::launch::async, [] {
        CyclicTimer timer;

        timer.Start(100);
    });

    ASSERT_THROW(result.get(), InvalidOperationException);
}

TEST(CyclicTimerTests, Start_CalledOnThreadWithEventDispatcher_CompletesSuccessfully) {
    auto result = QtConcurrent::run([] {
        CyclicTimer timer;

        timer.Start(100);
    });

    ASSERT_NO_THROW(result.waitForFinished());
}

} // namespace Diplomamunka::UnitTest
