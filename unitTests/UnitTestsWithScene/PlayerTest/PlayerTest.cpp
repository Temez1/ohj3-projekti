#include <QtTest>
#include <QCoreApplication>
#include <QGraphicsScene>

#include "Player.h"
#include "Bus.h"
#include "Kiosk.h"


class PlayerTest : public QObject
{
    Q_OBJECT

public:
    PlayerTest();
    ~PlayerTest();

private slots:
    void init();
    void cleanup();

    void jumpToBus_BusIsAtSameLocationPlayerIsNOTOnTheBus_PlayerIsOnTheBusAndReturnsTrue();
    void jumpToBus_BusIsAtSameLocationPlayerIsOnTheBus_PlayerIsOnTheBusAndReturnsFalse();
    void jumpToBus_BusIsNOTAtSameLocationPlayerIsNOTOnTheBus_PlayerIsNOTOnTheBusAndReturnsFalse();

    void dropFromBus_PlayerIsNOTOnTheBus_PlayerIsNOTOnTheBusAndReturnsFalse();
    void dropFromBus_PlayerIsOnTheBusAndBusIsNOTWaitingAtStop_PlayerIsOnTheBusAndReturnsFalse();
    void dropFromBus_PlayerIsOnTheBusAndBusIsWaitingAtStop_PlayerIsNOTOnTheBusAndReturnsTrue();

    void orderFood_PlayerAtKioskWithoutFood_PlayerHasOneFoodAndReturnsTrue();

    void Scenario_PlayerIsOnTheBusAndSceneAdvances_PlayerParentPosEqualsBusPos();
    void Scenario_PlayerDropsFromTheBusAndSceneAdvances_PlayerStaysAtStop();
private:
    QGraphicsScene *scene_;
    Player *player_;
    Stop *firstStop_;
    Stop *secondStop_;
    std::shared_ptr<BusLine> busline_;
    Bus *bus_;
    const float BUS_DEFAULT_SPEED_;
    Kiosk *kiosk_;
};

PlayerTest::PlayerTest():
    scene_(new QGraphicsScene()),
    player_(new Player("Test", scene_)),
    firstStop_(new Stop(QString("testStop1"), QPointF(100,100))),
    secondStop_(new Stop(QString("testStop2"), QPointF(200,100))),
    busline_(std::make_shared<BusLine>(BusLine("Test busline", {firstStop_, secondStop_}))),
    bus_(new Bus("Test Bus", busline_)),
    BUS_DEFAULT_SPEED_(bus_->getSpeedPixelsPerFrame()),
    kiosk_(new Kiosk())
{}

PlayerTest::~PlayerTest()
{}

void PlayerTest::init()
{
    firstStop_ = new Stop(QString("testStop1"), QPointF(100,100));
    secondStop_ = new Stop(QString("testStop2"), QPointF(200,100));

    busline_ = std::make_shared<BusLine>(BusLine("Test busline", {firstStop_, secondStop_}));
    bus_ = new Bus("Test Bus", busline_);

    kiosk_ = new Kiosk();
    kiosk_->setPos(firstStop_->pos());

    scene_ = new QGraphicsScene();
    scene_->addItem(firstStop_);
    scene_->addItem(secondStop_);
    scene_->addItem(bus_);
    scene_->addItem(kiosk_);

    player_ = new Player("Test player", scene_);
    scene_->addItem(player_);
}

void PlayerTest::cleanup()
{
    delete scene_;
}

void PlayerTest::jumpToBus_BusIsAtSameLocationPlayerIsNOTOnTheBus_PlayerIsOnTheBusAndReturnsTrue()
{
    player_->setPos(bus_->pos());

    auto jumpToBusReturnValue = player_->jumpToBus();

    QCOMPARE(player_->isOnTheBus(), true);
    QCOMPARE(jumpToBusReturnValue, true);
}

void PlayerTest::jumpToBus_BusIsAtSameLocationPlayerIsOnTheBus_PlayerIsOnTheBusAndReturnsFalse()
{
    player_->setPos(bus_->pos());
    player_->jumpToBus();

    auto jumpToBusReturnValue = player_->jumpToBus();

    QCOMPARE(player_->isOnTheBus(), true);
    QCOMPARE(jumpToBusReturnValue, false);
}

void PlayerTest::jumpToBus_BusIsNOTAtSameLocationPlayerIsNOTOnTheBus_PlayerIsNOTOnTheBusAndReturnsFalse()
{
    player_->setPos(bus_->pos() + QPointF(200,200));

    auto jumpToBusReturnValue = player_->jumpToBus();

    QCOMPARE(player_->isOnTheBus(), false);
    QCOMPARE(jumpToBusReturnValue, false);
}

void PlayerTest::dropFromBus_PlayerIsNOTOnTheBus_PlayerIsNOTOnTheBusAndReturnsFalse()
{
    auto dropFromBusReturnValue = player_->dropFromBus();

    QCOMPARE(player_->isOnTheBus(), false);
    QCOMPARE(dropFromBusReturnValue, false);
}

void PlayerTest::dropFromBus_PlayerIsOnTheBusAndBusIsNOTWaitingAtStop_PlayerIsOnTheBusAndReturnsFalse()
{
    player_->setPos(bus_->pos());
    player_->jumpToBus();

    auto dropFromBusReturnValue = player_->dropFromBus();

    QCOMPARE(player_->isOnTheBus(), true);
    QCOMPARE(dropFromBusReturnValue, false);
}

void PlayerTest::dropFromBus_PlayerIsOnTheBusAndBusIsWaitingAtStop_PlayerIsNOTOnTheBusAndReturnsTrue()
{
    player_->setPos(bus_->pos());
    player_->jumpToBus();
    int stepsLimit = 1000;
    int steps = 0;

    // Reach the next stop, so bus starts waiting
    while (not bus_->isWaitingAtStop()) {
        if (steps > stepsLimit){
            QFAIL("Readhed limit but didn't reach second stop");
        }
        scene_->advance();
        steps += 1;
    }

    auto dropFromBusReturnValue = player_->dropFromBus();

    QCOMPARE(player_->isOnTheBus(), false);
    QCOMPARE(dropFromBusReturnValue, true);
}

void PlayerTest::orderFood_PlayerAtKioskWithoutFood_PlayerHasOneFoodAndReturnsTrue()
{
    player_->setPos(kiosk_->pos());

    auto orderFoodReturnValue = player_->orderFood();
    auto playerFoodsAmount = player_->getFoods().length();

    QCOMPARE(playerFoodsAmount, 1);
    QCOMPARE(orderFoodReturnValue, true);
}

void PlayerTest::Scenario_PlayerIsOnTheBusAndSceneAdvances_PlayerParentPosEqualsBusPos()
{
    player_->setPos(bus_->pos());
    player_->jumpToBus();

    scene_->advance();
    auto playerParentPos = player_->parentItem()->pos();

    QCOMPARE(playerParentPos, bus_->pos());
}

void PlayerTest::Scenario_PlayerDropsFromTheBusAndSceneAdvances_PlayerStaysAtStop()
{
    player_->setPos(bus_->pos());
    player_->jumpToBus();
    int stepsLimit = 1000;
    int steps = 0;

    // Reach the next stop, so bus starts waiting
    while (not bus_->isWaitingAtStop()) {
        if (steps > stepsLimit){
            QFAIL("Readhed limit but didn't reach second stop");
        }
        scene_->advance();
        steps += 1;
    }

    auto playerPosBeforeDrop = bus_->pos();
    player_->dropFromBus();
    scene_->advance();
    auto playerPosAfterDrop = player_->pos();

    QCOMPARE(playerPosAfterDrop, playerPosBeforeDrop);
}


QTEST_MAIN(PlayerTest)

#include "PlayerTest.moc"
