#include <CyclicTimer.h>
#include <Exception.h>
#include <future>
#include <gmock/gmock.h>

using namespace testing;
using namespace Diplomamunka;

namespace Diplomamunka::UnitTest {

TEST(CyclicTimerTests, IsRunning_TimerHasBeenStarted_ReturnsTrue) {
    CyclicTimer timer;

    timer.start(100);

    ASSERT_THAT(timer.isRunning(), IsTrue());
}

TEST(CyclicTimerTests, IsRunning_TimerHasBeenStopped_ReturnsFalse) {
    CyclicTimer timer;

    timer.start(100);
    timer.stop();

    ASSERT_THAT(timer.isRunning(), IsFalse());
}

TEST(CyclicTimerTests, Start_TimerIsAlreadyRunning_ThrowsException) {
    CyclicTimer timer;
    timer.start(100);

    ASSERT_THROW(timer.start(200), InvalidOperationException);
}

TEST(CyclicTimerTests, Start_NegativeIntervalWasProvided_ThrowsException) {
    CyclicTimer timer;

    ASSERT_THROW(timer.start(-10), ArgumentOutOfRangeException);
}

TEST(CyclicTimerTests, Start_CalledOnThreadWithoutEventDispatcher_ThrowsException) {
    auto result = std::async(std::launch::async, [] {
        CyclicTimer timer;
        timer.start(100);
    });

    ASSERT_THROW(result.get(), InvalidOperationException);
}

TEST(CyclicTimerTests, Start_InitiatedFromAnotherThread_ThrowsException) {
    CyclicTimer timer;

    auto result = std::async(std::launch::async, [&timer] {
        timer.start(100);
    });

    ASSERT_THROW(result.get(), InvalidOperationException);
}

TEST(CyclicTimerTests, Stop_TimerIsNotRunning_ThrowsException) {
    CyclicTimer timer;

    ASSERT_THROW(timer.stop(), InvalidOperationException);
}

TEST(CyclicTimerTests, Stop_InitiatedFromAnotherThread_ThrowsException) {
    CyclicTimer timer;
    timer.start(100);

    auto result = std::async(std::launch::async, [&timer] {
        timer.stop();
    });

    ASSERT_THROW(result.get(), InvalidOperationException);
}

} // namespace Diplomamunka::UnitTest
