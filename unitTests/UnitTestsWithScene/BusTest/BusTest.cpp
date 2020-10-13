#include <QtTest>
#include <QCoreApplication>
#include <QGraphicsScene>

#include "Bus.h"
#include "Stop.h"
#include "BusLine.h"

class BusTest : public QObject
{
    Q_OBJECT

public:
    BusTest();

private slots:
    void init();
    void cleanup();

    void initBus_BusStartingAtInvalidStopIndex_throwsOutOfRange();
    void initBus_BusStartingAtFirstStop_ReturnsBusPositionAtFirstStop();
    void initBus_BusStartingAtSecondStop_ReturnsBusPositionAtSecondStop();

    void advance_StartingFromFirstStopAdvancingOnce_BusVelocityIsTowardsSecondStop();
    void advance_StartingFromFirstStopToSecondStop_NewPosIsBusSpeedCloserToSecondStop();

private:
    Stop *firstStop_;
    Stop *secondStop_;
    std::shared_ptr<BusLine> busline_;
    Bus *bus_;
    const float BUS_DEFAULT_SPEED_;
    float busSpeed_;
    QGraphicsScene *scene_;
    const int FIRST_STOP_INDEX = 0;
    const int SECOND_STOP_INDEX = 1;
    const int BUS_DIRECTION_FROM_START_TO_END_ = 1;
    const int BUS_DIRECTION_FROM_END_TO_START_ = -1;
};

BusTest::BusTest():
    firstStop_(new Stop(QString("testStop1"), QPointF(100,100))),
    secondStop_(new Stop(QString("testStop2"), QPointF(200,100))),
    busline_(std::make_shared<BusLine>(BusLine("Test busline", {firstStop_, secondStop_}))),
    bus_(new Bus("Test Bus", busline_)),
    BUS_DEFAULT_SPEED_(bus_->getSpeedPixelsPerFrame()),
    busSpeed_(BUS_DEFAULT_SPEED_),
    scene_(new QGraphicsScene())
{}

void BusTest::init()
{
    firstStop_ = new Stop(QString("testStop1"), QPointF(100,100));
    secondStop_ = new Stop(QString("testStop2"), QPointF(200,100));

    busline_ = std::make_shared<BusLine>(BusLine("Test busline", {firstStop_, secondStop_}));
    bus_ = new Bus("Test Bus", busline_);

    scene_ = new QGraphicsScene();
    scene_->addItem(firstStop_);
    scene_->addItem(secondStop_);
    scene_->addItem(bus_);
}

void BusTest::cleanup()
{
    delete scene_;
}

void BusTest::initBus_BusStartingAtInvalidStopIndex_throwsOutOfRange()
{
    int invalidStartingStopIndex = -1;
    delete bus_;

    try {
        bus_ = new Bus("test", busline_, BUS_DEFAULT_SPEED_, invalidStartingStopIndex, BUS_DIRECTION_FROM_START_TO_END_);
        QFAIL("initBus did not throw out of range exception!");
    }
    catch (const std::out_of_range &e) {
        bus_ = new Bus("Bus creation failed, so create a proper one so it can be deleted in cleanup", busline_);
        qDebug() << e.what();
    }
}

void BusTest::initBus_BusStartingAtFirstStop_ReturnsBusPositionAtFirstStop()
{
    int startingStop = FIRST_STOP_INDEX;
    delete bus_;
    bus_ = new Bus("test", busline_, BUS_DEFAULT_SPEED_, startingStop, BUS_DIRECTION_FROM_START_TO_END_);

    QPointF busStartingPos = bus_->pos();

    QCOMPARE(busStartingPos, firstStop_->pos());
}

void BusTest::initBus_BusStartingAtSecondStop_ReturnsBusPositionAtSecondStop()
{
    int startingStop = SECOND_STOP_INDEX;
    delete bus_;
    bus_ = new Bus("test", busline_, BUS_DEFAULT_SPEED_, startingStop, BUS_DIRECTION_FROM_START_TO_END_);

    QPointF busStartingPos = bus_->pos();

    QCOMPARE(busStartingPos, secondStop_->pos());
}

void BusTest::advance_StartingFromFirstStopAdvancingOnce_BusVelocityIsTowardsSecondStop()
{
    auto expectedVelocity = QVector2D(secondStop_->pos() - firstStop_->pos()).normalized() * BUS_DEFAULT_SPEED_;

    auto busVelocity = bus_->getVelocityPixelsPerFrame();

    QCOMPARE(busVelocity, expectedVelocity);
}

void BusTest::advance_StartingFromFirstStopToSecondStop_NewPosIsBusSpeedCloserToSecondStop()
{
    auto oldPos = bus_->pos();
    // TODO bus direction times speed + old pos = new pos
    // auto oldPosSpeedAmountCloserToSecondStop =

    scene_->advance();
    auto newPos = bus_->pos();


}

QTEST_MAIN(BusTest)

#include "BusTest.moc"
