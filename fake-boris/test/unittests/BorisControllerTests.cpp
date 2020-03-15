#include <BorisControllerTests.h>
#include <Exception.h>

using namespace testing;
using namespace Diplomamunka;

namespace Diplomamunka::UnitTest {

TEST_F(BorisControllerTests, Constructor_IOPortPtrIsNullptr_ThrowsArgumentNullException) {
    ASSERT_THROW(BorisController(nullptr, m_FakeTimerPtr), ArgumentNullException);
}

TEST_F(BorisControllerTests, Constructor_TimerPtrIsNullptr_ThrowsArgumentNullException) {
    ASSERT_THROW(BorisController(m_FakeIOPortPtr, nullptr), ArgumentNullException);
}

TEST_F(BorisControllerTests, IsActive_ControllerStarted_ReturnsTrue) {
    BorisController controller(m_FakeIOPortPtr, m_FakeTimerPtr);

    controller.Start();

    ASSERT_THAT(controller.IsActive(), IsTrue());
}

TEST_F(BorisControllerTests, IsActive_ControllerStartedThenStopped_ReturnsFalse) {
    BorisController controller(m_FakeIOPortPtr, m_FakeTimerPtr);

    controller.Start();
    controller.Stop();

    ASSERT_THAT(controller.IsActive(), IsFalse());
}

TEST_F(BorisControllerTests, IsActive_OpeningIOPortThrowsException_ReturnsFalse) {
    EXPECT_CALL(*m_FakeIOPortPtr, Open(_)).WillOnce(Throw(IOException("Test")));

    BorisController controller(m_FakeIOPortPtr, m_FakeTimerPtr);

    ASSERT_THROW(controller.Start(), IOException);
    ASSERT_THAT(controller.IsActive(), IsFalse());
}

TEST_F(BorisControllerTests, IsActive_StartingTimerThrowsException_ReturnsFalse) {
    EXPECT_CALL(*m_FakeTimerPtr, Start(_)).WillOnce(Throw(ArgumentOutOfRangeException("Test")));

    BorisController controller(m_FakeIOPortPtr, m_FakeTimerPtr);

    ASSERT_THROW(controller.Start(), ArgumentOutOfRangeException);
    ASSERT_THAT(controller.IsActive(), IsFalse());
}

TEST_F(BorisControllerTests, Start_Called_OpensPortBeforeStartingTimer) {
    InSequence expectOrderedCalls;
    EXPECT_CALL(*m_FakeIOPortPtr, Open(_));
    EXPECT_CALL(*m_FakeTimerPtr, Start(_));

    BorisController controller(m_FakeIOPortPtr, m_FakeTimerPtr);

    controller.Start();
}

TEST_F(BorisControllerTests, Stop_Called_StopsTimerBeforeClosingPort) {
    InSequence expectOrderedCalls;
    EXPECT_CALL(*m_FakeTimerPtr, Stop());
    EXPECT_CALL(*m_FakeIOPortPtr, Close());

    BorisController controller(m_FakeIOPortPtr, m_FakeTimerPtr);

    controller.Stop();
}

TEST_F(BorisControllerTests, Destructor_ControllerIsActive_StopsTimerBeforeClosingPort) {
    InSequence expectOrderedCalls;
    EXPECT_CALL(*m_FakeTimerPtr, Stop());
    EXPECT_CALL(*m_FakeIOPortPtr, Close());

    BorisController controller(m_FakeIOPortPtr, m_FakeTimerPtr);

    controller.Start();
}

TEST_F(BorisControllerTests, Destructor_ControllerIsNotActive_DoesNothing) {
    EXPECT_CALL(*m_FakeTimerPtr, Stop()).Times(0);
    EXPECT_CALL(*m_FakeIOPortPtr, Close()).Times(0);

    BorisController(m_FakeIOPortPtr, m_FakeTimerPtr);
}

TEST_F(BorisControllerTests, Output_CommunicationHasBeenStarted_AppearsInOutgoingData) {
    EXPECT_CALL(*m_FakeIOPortPtr, Write({"\xba\xc0\xde\xb9"}));

    BorisController controller(m_FakeIOPortPtr, m_FakeTimerPtr);
    controller.SetOutput(0xc0de);

    controller.Start();
    m_FakeTimerPtr->Elapsed();
}

TEST_F(BorisControllerTests, Input_DataOfCorrectLengthWasReceived_ChangesToReceivedData) {
    EXPECT_CALL(*m_FakeIOPortPtr, Read()).WillOnce(Return("\xc0\xde"));

    BorisController controller(m_FakeIOPortPtr, m_FakeTimerPtr);
    controller.Start();

    m_FakeIOPortPtr->DataReceived();

    ASSERT_THAT(controller.GetInput(), Eq(0xc0de));
}

TEST_F(BorisControllerTests, Input_TooShortDataWasReceived_RemainsUnchanged) {
    EXPECT_CALL(*m_FakeIOPortPtr, Read()).WillOnce(Return("\xc0"));

    BorisController controller(m_FakeIOPortPtr, m_FakeTimerPtr);
    controller.Start();

    m_FakeIOPortPtr->DataReceived();

    ASSERT_THAT(controller.GetInput(), Eq(0));
}

TEST_F(BorisControllerTests, Input_TooLongDataWasReceived_RemainsUnchanged) {
    EXPECT_CALL(*m_FakeIOPortPtr, Read()).WillOnce(Return("\xc0\xde\x09"));

    BorisController controller(m_FakeIOPortPtr, m_FakeTimerPtr);
    controller.Start();

    m_FakeIOPortPtr->DataReceived();

    ASSERT_THAT(controller.GetInput(), Eq(0));
}

} // namespace Diplomamunka::UnitTest
