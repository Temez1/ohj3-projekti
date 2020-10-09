#include <vector>
#include <QtTest>

#include "BusLine.h"

class BusLineTest : public QObject
{
    Q_OBJECT
public:
    BusLineTest();

private slots:
    void init();
    void cleanup();

    void initBusLine_withoutStops_ThrowsError();
    void initBusLine_TwoStops_LastStopIsValid();

    void addStop_AfterTwoStopsAreAdded_checkLastStopIsValid();

    void getNextStop_InvalidDirection_ThrowsError();
    void getNextStop_TwoStopsAtFirstStopGoingFromStartToEnd_ReturnsSecondStopGoingFromStartToEnd();
    void getNextStop_TwoStopsAtSecondStopGoingFromEndToStart_ReturnsFirstStopGoingFromEndToStart();
    void getNextStop_ThreeStopsAtSecondStopGoingFromStartToEnd_ReturnsThirdStopGoingFromStartToEnd();
    void getNextStop_ThreeStopsAtSecondStopGoingFromEndToStart_ReturnsFirstStopGoingFromEndToStart();
    void getNextStop_ThreeStopsAtThirdStopGoingFromStartToEnd_ReturnsSecondStopGoingFromEndToStart();
    void getNextStop_ThreeStopsAtFirstStopGoingFromEndToStart_ReturnsSecondStopGoingFromStartToEnd();

private:
    BusLine *busline_;
    const int FIRST_STOP_ = 0;
    const int SECOND_STOP_ = 1;
    const int BUS_DIRECTION_FROM_START_TO_END_ = 1;
    const int BUS_DIRECTION_FROM_END_TO_START_ = -1;
};

BusLineTest::BusLineTest():
    busline_(new BusLine("testBusLine",
            std::vector<QGraphicsSvgItem *> {2, new QGraphicsSvgItem()}))
{}

void BusLineTest::init()
{
    // {} shorthand to init vector
    busline_ = new BusLine("testBusLine", {2, new QGraphicsSvgItem()});
}

void BusLineTest::cleanup()
{
    delete busline_;
}

void BusLineTest::initBusLine_withoutStops_ThrowsError()
{
    try {
        BusLine("Failing", {});
    }
    catch (const std::invalid_argument &e) {
        qDebug() << e.what();
    }
}

void BusLineTest::initBusLine_TwoStops_LastStopIsValid()
{
    QCOMPARE(busline_->lastStop, 1);
}

void BusLineTest::addStop_AfterTwoStopsAreAdded_checkLastStopIsValid()
{
    int lastStopBeforeAdding = busline_->lastStop;
    busline_->addStop(new QGraphicsSvgItem());
    busline_->addStop(new QGraphicsSvgItem());
    int lastStopAfterAdding = busline_->lastStop;

    int lastStopBeforeAddingPlusTwo = lastStopBeforeAdding + 2;

    QCOMPARE(lastStopAfterAdding, lastStopBeforeAddingPlusTwo);
}

void BusLineTest::getNextStop_InvalidDirection_ThrowsError()
{
    int invalidDirection = 0;

    try {
        busline_->getNextStop(FIRST_STOP_, invalidDirection);
    }
    catch (const std::invalid_argument &e) {
        qDebug() << e.what();
    }
}

void BusLineTest::getNextStop_TwoStopsAtFirstStopGoingFromStartToEnd_ReturnsSecondStopGoingFromStartToEnd()
{
    std::pair<int,int> nextStop = busline_->getNextStop(FIRST_STOP_, BUS_DIRECTION_FROM_START_TO_END_);

    QCOMPARE(nextStop.first , SECOND_STOP_);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_START_TO_END_);
}

void BusLineTest::getNextStop_TwoStopsAtSecondStopGoingFromEndToStart_ReturnsFirstStopGoingFromEndToStart()
{
    std::pair<int,int> nextStop = busline_->getNextStop(SECOND_STOP_, BUS_DIRECTION_FROM_END_TO_START_);

    QCOMPARE(nextStop.first, FIRST_STOP_);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_END_TO_START_);
}

void BusLineTest::getNextStop_ThreeStopsAtSecondStopGoingFromStartToEnd_ReturnsThirdStopGoingFromStartToEnd()
{
    busline_->addStop(new QGraphicsSvgItem());
    int thirdStop = busline_->lastStop;

    std::pair<int,int> nextStop = busline_->getNextStop(SECOND_STOP_, BUS_DIRECTION_FROM_START_TO_END_);

    QCOMPARE(nextStop.first, thirdStop);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_START_TO_END_);
}

void BusLineTest::getNextStop_ThreeStopsAtSecondStopGoingFromEndToStart_ReturnsFirstStopGoingFromEndToStart()
{
    busline_->addStop(new QGraphicsSvgItem());

    std::pair<int,int> nextStop = busline_->getNextStop(SECOND_STOP_, BUS_DIRECTION_FROM_END_TO_START_);

    QCOMPARE(nextStop.first, FIRST_STOP_);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_END_TO_START_);
}

void BusLineTest::getNextStop_ThreeStopsAtThirdStopGoingFromStartToEnd_ReturnsSecondStopGoingFromEndToStart()
{
    busline_->addStop(new QGraphicsSvgItem());
    int thirdStop = busline_->lastStop;

    std::pair<int,int> nextStop = busline_->getNextStop(thirdStop, BUS_DIRECTION_FROM_START_TO_END_);

    QCOMPARE(nextStop.first, SECOND_STOP_);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_END_TO_START_);
}

void BusLineTest::getNextStop_ThreeStopsAtFirstStopGoingFromEndToStart_ReturnsSecondStopGoingFromStartToEnd()
{
    busline_->addStop(new QGraphicsSvgItem());

    std::pair<int,int> nextStop = busline_->getNextStop(FIRST_STOP_, BUS_DIRECTION_FROM_END_TO_START_);

    QCOMPARE(nextStop.first, SECOND_STOP_);
    QCOMPARE(nextStop.second, BUS_DIRECTION_FROM_START_TO_END_);
}

QTEST_APPLESS_MAIN(BusLineTest)

#include "BusLineTest.moc"
