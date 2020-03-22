#include <CyclicTimer.h>
#include <Exception.h>
#include <future>
#include <gmock/gmock.h>

using namespace testing;
using namespace Diplomamunka;

namespace Diplomamunka::UnitTest {

TEST(CyclicTimerTests, IsRunning_TimerHasBeenStarted_ReturnsTrue) {
    CyclicTimer timer;

    timer.Start(100);

    ASSERT_THAT(timer.IsRunning(), IsTrue());
}

TEST(CyclicTimerTests, IsRunning_TimerHasBeenStopped_ReturnsFalse) {
    CyclicTimer timer;

    timer.Start(100);
    timer.Stop();

    ASSERT_THAT(timer.IsRunning(), IsFalse());
}

TEST(CyclicTimerTests, Start_TimerIsAlreadyRunning_ThrowsException) {
    CyclicTimer timer;
    timer.Start(100);

    ASSERT_THROW(timer.Start(200), InvalidOperationException);
}

TEST(CyclicTimerTests, Start_NegativeIntervalWasProvided_ThrowsException) {
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

TEST(CyclicTimerTests, Start_InitiatedFromAnotherThread_ThrowsException) {
    CyclicTimer timer;

    auto result = std::async(std::launch::async, [&timer] { timer.Start(100); });

    ASSERT_THROW(result.get(), InvalidOperationException);
}

TEST(CyclicTimerTests, Stop_TimerIsNotRunning_ThrowsException) {
    CyclicTimer timer;

    ASSERT_THROW(timer.Stop(), InvalidOperationException);
}

TEST(CyclicTimerTests, Stop_InitiatedFromAnotherThread_ThrowsException) {
    CyclicTimer timer;
    timer.Start(100);

    auto result = std::async(std::launch::async, [&timer] { timer.Stop(); });

    ASSERT_THROW(result.get(), InvalidOperationException);
}

} // namespace Diplomamunka::UnitTest
