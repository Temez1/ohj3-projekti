#include <QtTest>

#include "gameObjects/BusLine.h"
#include "gameObjects/graphical/Stop.h"

class BusLineTest : public QObject
{
    Q_OBJECT

public:
    BusLineTest();
    ~BusLineTest();

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
    BusLine *busline_;
    const int FIRST_STOP_INDEX = 0;
    const int SECOND_STOP_INDEX = 1;
    const int BUS_DIRECTION_FROM_START_TO_END_ = 1;
    const int BUS_DIRECTION_FROM_END_TO_START_ = -1;
};

BusLineTest::BusLineTest():
    firstStop_(new Stop(QString("testStop1"), QPointF(100,100))),
    secondStop_(new Stop(QString("testStop2"), QPointF(200,100))),
    busline_(new BusLine("testBusLine", {firstStop_, secondStop_}))
{}

void BusLineTest::init()
{
    firstStop_ = new Stop(QString("testStop1"), QPointF(100,100));
    secondStop_ = new Stop(QString("testStop2"), QPointF(200,100));
    busline_ = new BusLine("testBusLine", {firstStop_, secondStop_});
}

void BusLineTest::cleanup()
{
    delete firstStop_;
    delete secondStop_;
    delete busline_;
}

void BusLineTest::initBusLine_withoutStops_ThrowsInvalidArgument()
{
    try {
        BusLine("Failing", {});
        QFAIL("initBusLine did not throw invalid argument exception!");
    }
    catch (const std::invalid_argument &e) {
        qDebug() << e.what();
    }
}

void BusLineTest::initBusLine_TwoStops_LastStopIsValid()
{
    QCOMPARE(busline_->lastStopIndex, 1);
}

void BusLineTest::addStop_AfterTwoStopsAreAdded_checkLastStopIndexIsValid()
{
    int lastStopIndexBeforeAdding = busline_->lastStopIndex;
    busline_->addStop(new Stop(QString("testStop"), QPointF(0,0)));
    busline_->addStop(new Stop(QString("testStop"), QPointF(0,0)));
    int lastStopIndexAfterAdding = busline_->lastStopIndex;

    int lastStopIndexBeforeAddingPlusTwo = lastStopIndexBeforeAdding + 2;

    QCOMPARE(lastStopIndexAfterAdding, lastStopIndexBeforeAddingPlusTwo);
}

void BusLineTest::getNextStopIndexAndNewDirection_InvalidDirection_ThrowsInvalidArgument()
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

void BusLineTest::getNextStopIndexAndNewDirection_InvalidStopIndex_ThrowsOutOfRange()
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

void BusLineTest::getNextStopIndexAndNewDirection_TwoStopsAtFirstStopGoingFromStartToEnd_ReturnsSecondStopGoingFromStartToEnd()
{
    std::pair<int,int> nextStop = busline_->getNextStopIndexAndNewDirection(FIRST_STOP_INDEX, BUS_DIRECTION_FROM_START_TO_END_);

    QCOMPARE(nextStop.first , SECOND_STOP_INDEX);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_START_TO_END_);
}

void BusLineTest::getNextStopIndexAndNewDirection_TwoStopsAtSecondStopGoingFromEndToStart_ReturnsFirstStopGoingFromEndToStart()
{
    std::pair<int,int> nextStop = busline_->getNextStopIndexAndNewDirection(SECOND_STOP_INDEX, BUS_DIRECTION_FROM_END_TO_START_);

    QCOMPARE(nextStop.first, FIRST_STOP_INDEX);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_END_TO_START_);
}

void BusLineTest::getNextStopIndexAndNewDirection_ThreeStopsAtSecondStopGoingFromStartToEnd_ReturnsLastStopGoingFromStartToEnd()
{
    busline_->addStop(new Stop(QString("testStop"), QPointF(0,0)));
    int lastStop = busline_->lastStopIndex;

    std::pair<int,int> nextStop = busline_->getNextStopIndexAndNewDirection(SECOND_STOP_INDEX, BUS_DIRECTION_FROM_START_TO_END_);

    QCOMPARE(nextStop.first, lastStop);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_START_TO_END_);
}

void BusLineTest::getNextStopIndexAndNewDirection_ThreeStopsAtSecondStopGoingFromEndToStart_ReturnsFirstStopGoingFromEndToStart()
{
    busline_->addStop(new Stop(QString("testStop"), QPointF(0,0)));

    std::pair<int,int> nextStop = busline_->getNextStopIndexAndNewDirection(SECOND_STOP_INDEX, BUS_DIRECTION_FROM_END_TO_START_);

    QCOMPARE(nextStop.first, FIRST_STOP_INDEX);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_END_TO_START_);
}

void BusLineTest::getNextStopIndexAndNewDirection_ThreeStopsAtLastStopGoingFromStartToEnd_ReturnsSecondStopGoingFromEndToStart()
{
    busline_->addStop(new Stop(QString("testStop"), QPointF(0,0)));
    int lastStop = busline_->lastStopIndex;

    std::pair<int,int> nextStop = busline_->getNextStopIndexAndNewDirection(lastStop, BUS_DIRECTION_FROM_START_TO_END_);

    QCOMPARE(nextStop.first, SECOND_STOP_INDEX);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_END_TO_START_);
}

void BusLineTest::getNextStopIndexAndNewDirection_ThreeStopsAtFirstStopGoingFromEndToStart_ReturnsSecondStopGoingFromStartToEnd()
{
    busline_->addStop(new Stop(QString("testStop"), QPointF(0,0)));

    std::pair<int,int> nextStop = busline_->getNextStopIndexAndNewDirection(FIRST_STOP_INDEX, BUS_DIRECTION_FROM_END_TO_START_);

    QCOMPARE(nextStop.first, SECOND_STOP_INDEX);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_START_TO_END_);
}

void BusLineTest::getStopPosition_TwoStopsStopIndexGreaterThanStopSize_ThrowsOutOfRange()
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

void BusLineTest::getStopPosition_TwoStopsStopIndexLessThanZero_ThrowsOutOfRange()
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

void BusLineTest::getStopPosition_TwoStopsStopIndexFirstStop_ReturnsFirstStopPosition()
{
    QPointF firstStopPosition = busline_->getStopPosition(FIRST_STOP_INDEX);

    QCOMPARE(firstStopPosition, firstStop_->pos());
}

void BusLineTest::getStopPostiion_ThreeStopsStopIndexLastStop_ReturnsLastStopPosition()
{
    QPointF expectedLastStopPosition = QPointF(500,500);
    busline_->addStop(new Stop(QString("testStop3"), expectedLastStopPosition));
    int lastStopIndex = busline_->lastStopIndex;

    QPointF actualLastStopPosition = busline_->getStopPosition(lastStopIndex);

    QCOMPARE(actualLastStopPosition, expectedLastStopPosition);
}



BusLineTest::~BusLineTest()
{

}

QTEST_APPLESS_MAIN(BusLineTest)

#include "BusLineTest.moc"
