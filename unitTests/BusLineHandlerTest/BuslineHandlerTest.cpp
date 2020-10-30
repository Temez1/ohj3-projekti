#include <QtTest>

#include "gameObjects/handlers/BusLineHandler.h"
#include "gameObjects/graphical/Stop.h"

class BusLineHandlerTest : public QObject
{
    Q_OBJECT

public:
    BusLineHandlerTest();
    ~BusLineHandlerTest();

private slots:
    void init();
    void cleanup();

    void initBusLine_withoutStops_ThrowsInvalidArgument();
    void initBusLine_TwoStops_LastStopIsValid();

    void addStop_AfterTwoStopsAreAdded_checkLastStopIndexIsValid();

    void getNextStopIndexAndNewDirection_InvalidDirection_ThrowsInvalidArgument();
    void getNextStopIndexAndNewDirection_InvalidStopIndex_ThrowsOutOfRange();
    void getNextStopIndexAndNewDirection_TwoStopsAtFirstStopGoingFromStartToEnd_ReturnsSecondStopGoingFromStartToEnd();
    void getNextStopIndexAndNewDirection_TwoStopsAtSecondStopGoingFromEndToStart_ReturnsFirstStopGoingFromEndToStart();
    void getNextStopIndexAndNewDirection_ThreeStopsAtSecondStopGoingFromStartToEnd_ReturnsLastStopGoingFromStartToEnd();
    void getNextStopIndexAndNewDirection_ThreeStopsAtSecondStopGoingFromEndToStart_ReturnsFirstStopGoingFromEndToStart();
    void getNextStopIndexAndNewDirection_ThreeStopsAtLastStopGoingFromStartToEnd_ReturnsSecondStopGoingFromEndToStart();
    void getNextStopIndexAndNewDirection_ThreeStopsAtFirstStopGoingFromEndToStart_ReturnsSecondStopGoingFromStartToEnd();

    void getStopPosition_TwoStopsStopIndexGreaterThanStopSize_ThrowsOutOfRange();
    void getStopPosition_TwoStopsStopIndexLessThanZero_ThrowsOutOfRange();
    void getStopPosition_TwoStopsStopIndexFirstStop_ReturnsFirstStopPosition();
    void getStopPostiion_ThreeStopsStopIndexLastStop_ReturnsLastStopPosition();

private:
    Stop *firstStop_;
    Stop *secondStop_;
    BusLineHandler *busline_;
    const int FIRST_STOP_INDEX = 0;
    const int SECOND_STOP_INDEX = 1;
    const int BUS_DIRECTION_FROM_START_TO_END_ = 1;
    const int BUS_DIRECTION_FROM_END_TO_START_ = -1;
};

BusLineHandlerTest::BusLineHandlerTest():
    firstStop_(new Stop(QString("testStop1"), QPointF(100,100))),
    secondStop_(new Stop(QString("testStop2"), QPointF(200,100))),
    busline_(new BusLineHandler("testBusLine", {firstStop_, secondStop_}))
{}

void BusLineHandlerTest::init()
{
    firstStop_ = new Stop(QString("testStop1"), QPointF(100,100));
    secondStop_ = new Stop(QString("testStop2"), QPointF(200,100));
    busline_ = new BusLineHandler("testBusLine", {firstStop_, secondStop_});
}

void BusLineHandlerTest::cleanup()
{
    delete firstStop_;
    delete secondStop_;
    delete busline_;
}

void BusLineHandlerTest::initBusLine_withoutStops_ThrowsInvalidArgument()
{
    try {
        BusLineHandler("Failing", {});
        QFAIL("initBusLine did not throw invalid argument exception!");
    }
    catch (const std::invalid_argument &e) {
        qDebug() << e.what();
    }
}

void BusLineHandlerTest::initBusLine_TwoStops_LastStopIsValid()
{
    QCOMPARE(busline_->lastStopIndex, 1);
}

void BusLineHandlerTest::addStop_AfterTwoStopsAreAdded_checkLastStopIndexIsValid()
{
    int lastStopIndexBeforeAdding = busline_->lastStopIndex;
    busline_->addStop(new Stop(QString("testStop"), QPointF(0,0)));
    busline_->addStop(new Stop(QString("testStop"), QPointF(0,0)));
    int lastStopIndexAfterAdding = busline_->lastStopIndex;

    int lastStopIndexBeforeAddingPlusTwo = lastStopIndexBeforeAdding + 2;

    QCOMPARE(lastStopIndexAfterAdding, lastStopIndexBeforeAddingPlusTwo);
}

void BusLineHandlerTest::getNextStopIndexAndNewDirection_InvalidDirection_ThrowsInvalidArgument()
{
    int invalidDirection = 0;

    try {
        busline_->getNextStopIndexAndNewDirection(FIRST_STOP_INDEX, invalidDirection);
        QFAIL("getNextStopIndexAndNewDirection did not throw invalid argument exception!");
    }
    catch (const std::invalid_argument &e) {
        qDebug() << e.what();
    }
}

void BusLineHandlerTest::getNextStopIndexAndNewDirection_InvalidStopIndex_ThrowsOutOfRange()
{
    int invalidStopIndex = -1;

    try {
        busline_->getNextStopIndexAndNewDirection(invalidStopIndex, BUS_DIRECTION_FROM_START_TO_END_);
        QFAIL("getNextStopIndexAndNewDirection did not throw out of range exception!");
    }
    catch (const std::out_of_range &e) {
        qDebug() << e.what();
    }
}

void BusLineHandlerTest::getNextStopIndexAndNewDirection_TwoStopsAtFirstStopGoingFromStartToEnd_ReturnsSecondStopGoingFromStartToEnd()
{
    std::pair<int,int> nextStop = busline_->getNextStopIndexAndNewDirection(FIRST_STOP_INDEX, BUS_DIRECTION_FROM_START_TO_END_);

    QCOMPARE(nextStop.first , SECOND_STOP_INDEX);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_START_TO_END_);
}

void BusLineHandlerTest::getNextStopIndexAndNewDirection_TwoStopsAtSecondStopGoingFromEndToStart_ReturnsFirstStopGoingFromEndToStart()
{
    std::pair<int,int> nextStop = busline_->getNextStopIndexAndNewDirection(SECOND_STOP_INDEX, BUS_DIRECTION_FROM_END_TO_START_);

    QCOMPARE(nextStop.first, FIRST_STOP_INDEX);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_END_TO_START_);
}

void BusLineHandlerTest::getNextStopIndexAndNewDirection_ThreeStopsAtSecondStopGoingFromStartToEnd_ReturnsLastStopGoingFromStartToEnd()
{
    busline_->addStop(new Stop(QString("testStop"), QPointF(0,0)));
    int lastStop = busline_->lastStopIndex;

    std::pair<int,int> nextStop = busline_->getNextStopIndexAndNewDirection(SECOND_STOP_INDEX, BUS_DIRECTION_FROM_START_TO_END_);

    QCOMPARE(nextStop.first, lastStop);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_START_TO_END_);
}

void BusLineHandlerTest::getNextStopIndexAndNewDirection_ThreeStopsAtSecondStopGoingFromEndToStart_ReturnsFirstStopGoingFromEndToStart()
{
    busline_->addStop(new Stop(QString("testStop"), QPointF(0,0)));

    std::pair<int,int> nextStop = busline_->getNextStopIndexAndNewDirection(SECOND_STOP_INDEX, BUS_DIRECTION_FROM_END_TO_START_);

    QCOMPARE(nextStop.first, FIRST_STOP_INDEX);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_END_TO_START_);
}

void BusLineHandlerTest::getNextStopIndexAndNewDirection_ThreeStopsAtLastStopGoingFromStartToEnd_ReturnsSecondStopGoingFromEndToStart()
{
    busline_->addStop(new Stop(QString("testStop"), QPointF(0,0)));
    int lastStop = busline_->lastStopIndex;

    std::pair<int,int> nextStop = busline_->getNextStopIndexAndNewDirection(lastStop, BUS_DIRECTION_FROM_START_TO_END_);

    QCOMPARE(nextStop.first, SECOND_STOP_INDEX);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_END_TO_START_);
}

void BusLineHandlerTest::getNextStopIndexAndNewDirection_ThreeStopsAtFirstStopGoingFromEndToStart_ReturnsSecondStopGoingFromStartToEnd()
{
    busline_->addStop(new Stop(QString("testStop"), QPointF(0,0)));

    std::pair<int,int> nextStop = busline_->getNextStopIndexAndNewDirection(FIRST_STOP_INDEX, BUS_DIRECTION_FROM_END_TO_START_);

    QCOMPARE(nextStop.first, SECOND_STOP_INDEX);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_START_TO_END_);
}

void BusLineHandlerTest::getStopPosition_TwoStopsStopIndexGreaterThanStopSize_ThrowsOutOfRange()
{
    int outOfRangeIndex = 2;

    try {
        busline_->getStopPosition(outOfRangeIndex);
        QFAIL("getStopPosition did not throw out of range exception!");
    }
    catch (const std::out_of_range &e) {
        qDebug() << e.what();
    }
}

void BusLineHandlerTest::getStopPosition_TwoStopsStopIndexLessThanZero_ThrowsOutOfRange()
{
    int outOfRangeIndex = -1;

    try {
        busline_->getStopPosition(outOfRangeIndex);
        QFAIL("getStopPosition did not throw out of range exception!");
    }
    catch (const std::out_of_range &e) {
        qDebug() << e.what();
    }
}

void BusLineHandlerTest::getStopPosition_TwoStopsStopIndexFirstStop_ReturnsFirstStopPosition()
{
    QPointF firstStopPosition = busline_->getStopPosition(FIRST_STOP_INDEX);

    QCOMPARE(firstStopPosition, firstStop_->pos());
}

void BusLineHandlerTest::getStopPostiion_ThreeStopsStopIndexLastStop_ReturnsLastStopPosition()
{
    QPointF expectedLastStopPosition = QPointF(500,500);
    busline_->addStop(new Stop(QString("testStop3"), expectedLastStopPosition));
    int lastStopIndex = busline_->lastStopIndex;

    QPointF actualLastStopPosition = busline_->getStopPosition(lastStopIndex);

    QCOMPARE(actualLastStopPosition, expectedLastStopPosition);
}



BusLineHandlerTest::~BusLineHandlerTest()
{

}

QTEST_APPLESS_MAIN(BusLineHandlerTest)

#include "BusLineHandlerTest.moc"
