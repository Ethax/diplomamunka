#include <BorisControllerTests.h>
#include <Exception.h>

using namespace testing;
using namespace Diplomamunka;

namespace Diplomamunka::UnitTest {

TEST_F(BorisControllerTests, Constructor_IOPortPtrIsNullptr_ThrowsArgumentNullException) {
    ASSERT_THROW(BorisController(nullptr, m_timerPtr), ArgumentNullException);
}

TEST_F(BorisControllerTests, Constructor_TimerPtrIsNullptr_ThrowsArgumentNullException) {
    ASSERT_THROW(BorisController(m_ioPortPtr, nullptr), ArgumentNullException);
}

TEST_F(BorisControllerTests, IsActive_ControllerStarted_ReturnsTrue) {
    BorisController controller(m_ioPortPtr, m_timerPtr);

    controller.start();

    ASSERT_THAT(controller.isActive(), IsTrue());
}

TEST_F(BorisControllerTests, IsActive_ControllerStartedThenStopped_ReturnsFalse) {
    BorisController controller(m_ioPortPtr, m_timerPtr);

    controller.start();
    controller.stop();

    ASSERT_THAT(controller.isActive(), IsFalse());
}

TEST_F(BorisControllerTests, IsActive_OpeningIOPortThrowsException_ReturnsFalse) {
    EXPECT_CALL(*m_ioPortPtr, open(_)).WillOnce(Throw(IOException("Test")));

    BorisController controller(m_ioPortPtr, m_timerPtr);

    ASSERT_THROW(controller.start(), IOException);
    ASSERT_THAT(controller.isActive(), IsFalse());
}

TEST_F(BorisControllerTests, IsActive_StartingTimerThrowsException_ReturnsFalse) {
    EXPECT_CALL(*m_timerPtr, start(_)).WillOnce(Throw(ArgumentOutOfRangeException("Test")));

    BorisController controller(m_ioPortPtr, m_timerPtr);

    ASSERT_THROW(controller.start(), ArgumentOutOfRangeException);
    ASSERT_THAT(controller.isActive(), IsFalse());
}

TEST_F(BorisControllerTests, Start_Called_OpensPortBeforeStartingTimer) {
    InSequence expectOrderedCalls;
    EXPECT_CALL(*m_ioPortPtr, open(_));
    EXPECT_CALL(*m_timerPtr, start(_));

    BorisController controller(m_ioPortPtr, m_timerPtr);

    controller.start();
}

TEST_F(BorisControllerTests, Stop_Called_StopsTimerBeforeClosingPort) {
    InSequence expectOrderedCalls;
    EXPECT_CALL(*m_timerPtr, stop());
    EXPECT_CALL(*m_ioPortPtr, close());

    BorisController controller(m_ioPortPtr, m_timerPtr);

    controller.stop();
}

TEST_F(BorisControllerTests, Destructor_ControllerIsActive_StopsTimerBeforeClosingPort) {
    InSequence expectOrderedCalls;
    EXPECT_CALL(*m_timerPtr, stop());
    EXPECT_CALL(*m_ioPortPtr, close());

    BorisController controller(m_ioPortPtr, m_timerPtr);

    controller.start();
}

TEST_F(BorisControllerTests, Destructor_ControllerIsNotActive_DoesNothing) {
    EXPECT_CALL(*m_timerPtr, stop()).Times(0);
    EXPECT_CALL(*m_ioPortPtr, close()).Times(0);

    BorisController(m_ioPortPtr, m_timerPtr);
}

TEST_F(BorisControllerTests, Output_CommunicationHasBeenStarted_AppearsInOutgoingData) {
    EXPECT_CALL(*m_ioPortPtr, write({"\xba\xc0\xde\xb9"}));

    BorisController controller(m_ioPortPtr, m_timerPtr);
    controller.output(0xc0de);

    controller.start();
    m_timerPtr->elapsed();
}

TEST_F(BorisControllerTests, Input_DataOfCorrectLengthWasReceived_ChangesToReceivedData) {
    EXPECT_CALL(*m_ioPortPtr, read()).WillOnce(Return("\xc0\xde"));

    BorisController controller(m_ioPortPtr, m_timerPtr);
    controller.start();

    m_ioPortPtr->dataReceived();

    ASSERT_THAT(controller.input(), Eq(0xc0de));
}

TEST_F(BorisControllerTests, Input_TooShortDataWasReceived_RemainsUnchanged) {
    EXPECT_CALL(*m_ioPortPtr, read()).WillOnce(Return("\xc0"));

    BorisController controller(m_ioPortPtr, m_timerPtr);
    controller.start();

    m_ioPortPtr->dataReceived();

    ASSERT_THAT(controller.input(), Eq(0));
}

TEST_F(BorisControllerTests, Input_TooLongDataWasReceived_RemainsUnchanged) {
    EXPECT_CALL(*m_ioPortPtr, read()).WillOnce(Return("\xc0\xde\x09"));

    BorisController controller(m_ioPortPtr, m_timerPtr);
    controller.start();

    m_ioPortPtr->dataReceived();

    ASSERT_THAT(controller.input(), Eq(0));
}

} // namespace Diplomamunka::UnitTest
