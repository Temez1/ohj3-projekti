#include <QtTest>
#include <QCoreApplication>
#include <QGraphicsScene>

#include "gameObjects/graphical/Player.h"

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
    void orderFood_PlayerNOTAtKioskWithoutFood_PlayerHasZeroFoodAndReturnsFalse();
    void orderFood_PlayerAtKioskWithMaxAmountOfFoods_PlayerHasMaxAmountOfFoodsAndReturnsFalse();

    void deliverFood_PlayerHasNoFood_PlayersHasNoFoodAndReturnsFalse();
    void deliverFood_PlayerHasFood_PlayersHasNoFoodAndReturnsTrue();

    void isFullOfFood_PlayerAtKioskWithMaxAmountOfFoods_PlayerIsFullOfFood();
    void isFullOfFood_PlayerAtKioskWithOneFood_PlayerIsNOTFullOfFood();

    void Scenario_PlayerIsOnTheBusAndSceneAdvances_PlayerParentPosEqualsBusPos();
    void Scenario_PlayerDropsFromTheBusAndSceneAdvances_PlayerStaysAtStop();
    void Scenario_PlayerOrdersFoodWithoutMoney_PlayerSignalsOutOfMoney();
    void Scenario_PlayerOrdersFood_PlayerSignalsPlayerOrderedFood();
    void Scenario_PlayerDeliversFood_PlayerSignalsPlayerDeliveredFood();
    void Scenario_PlayerDeliversFood_PlayerReceivesMoney();

private:
    const int KIOSK_FOOD_PRICE_ = 10;
    const int PLAYER_STARTING_MONEY_ = 50;
    const int PLAYER_MAX_AMOUNT_OF_FOOD_TO_CARRY = 2;

    QGraphicsScene *scene_;
    Stop *firstStop_;
    Stop *secondStop_;
    std::shared_ptr<BusLineHandler> busline_;
    Bus *bus_;
    const float BUS_DEFAULT_SPEED_;
    Kiosk *kiosk_;
    Player *player_;
};

PlayerTest::PlayerTest():
    scene_(new QGraphicsScene()),
    firstStop_(new Stop(QString("testStop1"), QPointF(100,100))),
    secondStop_(new Stop(QString("testStop2"), QPointF(200,100))),
    busline_(std::make_shared<BusLineHandler>(BusLineHandler("Test busline", {firstStop_, secondStop_}))),
    bus_(new Bus("Test Bus", busline_)),
    BUS_DEFAULT_SPEED_(bus_->getSpeedPixelsPerFrame()),
    kiosk_(new Kiosk(KIOSK_FOOD_PRICE_)),
    player_(new Player("Test", scene_, firstStop_, PLAYER_STARTING_MONEY_, PLAYER_MAX_AMOUNT_OF_FOOD_TO_CARRY))
{}

PlayerTest::~PlayerTest()
{}

void PlayerTest::init()
{
    kiosk_ = new Kiosk(KIOSK_FOOD_PRICE_);
    firstStop_ = new Stop(QString("testStop1"), QPointF(100,100), kiosk_);
    kiosk_->setParentItem(firstStop_);
    secondStop_ = new Stop(QString("testStop2"), QPointF(200,100));

    busline_ = std::make_shared<BusLineHandler>(BusLineHandler("Test busline", {firstStop_, secondStop_}));
    bus_ = new Bus("Test Bus", busline_);

    scene_ = new QGraphicsScene();
    scene_->addItem(kiosk_);
    scene_->addItem(firstStop_);
    scene_->addItem(secondStop_);
    scene_->addItem(bus_);

    player_ = new Player("Test player", scene_, firstStop_, PLAYER_STARTING_MONEY_, PLAYER_MAX_AMOUNT_OF_FOOD_TO_CARRY);
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
    auto orderFoodReturnValue = player_->orderFood();
    auto playerFoodsAmount = player_->getFoods().length();

    QCOMPARE(playerFoodsAmount, 1);
    QCOMPARE(orderFoodReturnValue, true);
}

void PlayerTest::orderFood_PlayerNOTAtKioskWithoutFood_PlayerHasZeroFoodAndReturnsFalse()
{
    player_->jumpToBus();

    auto orderFoodReturnValue = player_->orderFood();
    auto playerFoodsAmount = player_->getFoods().length();

    QCOMPARE(playerFoodsAmount, 0);
    QCOMPARE(orderFoodReturnValue, false);
}

void PlayerTest::orderFood_PlayerAtKioskWithMaxAmountOfFoods_PlayerHasMaxAmountOfFoodsAndReturnsFalse()
{
    for (int i = 0; i < player_->FOOD_MAX_AMOUNT; i++) {
        player_->orderFood();
    }

    auto orderFoodReturnValue = player_->orderFood();
    auto playerFoodsAmount = player_->getFoods().length();

    QCOMPARE(playerFoodsAmount, player_->FOOD_MAX_AMOUNT);
    QCOMPARE(orderFoodReturnValue, false);
}

void PlayerTest::deliverFood_PlayerHasNoFood_PlayersHasNoFoodAndReturnsFalse()
{
    auto deliverFoodReturnValue = player_->deliverFood();
    auto playerFoodsAmount = player_->getFoods().length();

    QCOMPARE(playerFoodsAmount, 0);
    QCOMPARE(deliverFoodReturnValue, false);
}

void PlayerTest::deliverFood_PlayerHasFood_PlayersHasNoFoodAndReturnsTrue()
{
    player_->orderFood();

    auto deliverFoodReturnValue = player_->deliverFood();
    auto playerFoodsAmount = player_->getFoods().length();

    QCOMPARE(playerFoodsAmount, 0);
    QCOMPARE(deliverFoodReturnValue, true);
}

void PlayerTest::isFullOfFood_PlayerAtKioskWithMaxAmountOfFoods_PlayerIsFullOfFood()
{
    player_->setPos(firstStop_->pos());

    for (int i = 0; i < player_->FOOD_MAX_AMOUNT; i++) {
        player_->orderFood();
    }

    auto isFullOfFoodReturnValue = player_->isFullOfFood();

    QCOMPARE(isFullOfFoodReturnValue, true);
}

void PlayerTest::isFullOfFood_PlayerAtKioskWithOneFood_PlayerIsNOTFullOfFood()
{
    player_->setPos(firstStop_->pos());
    player_->orderFood();

    auto isFullOfFoodReturnValue = player_->isFullOfFood();

    QCOMPARE(isFullOfFoodReturnValue, false);
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

void PlayerTest::Scenario_PlayerOrdersFoodWithoutMoney_PlayerSignalsOutOfMoney()
{
    player_ = new Player("persaukinen", scene_, firstStop_, 0, PLAYER_MAX_AMOUNT_OF_FOOD_TO_CARRY);
    QSignalSpy spy(player_, &Player::playerOutOfMoney);
    QVERIFY(spy.isValid());

    player_->orderFood();

    QCOMPARE(spy.count(), 1);
}

void PlayerTest::Scenario_PlayerOrdersFood_PlayerSignalsPlayerOrderedFood()
{
    QSignalSpy spy(player_, &Player::playerOrderedFood);
    QVERIFY(spy.isValid());

    player_->orderFood();

    QCOMPARE(spy.count(), 1);
}

void PlayerTest::Scenario_PlayerDeliversFood_PlayerSignalsPlayerDeliveredFood()
{
    player_->orderFood();
    QSignalSpy spy(player_, &Player::playerDeliveredFood);
    QVERIFY(spy.isValid());

    player_->deliverFood();

    QCOMPARE(spy.count(), 1);
}

void PlayerTest::Scenario_PlayerDeliversFood_PlayerReceivesMoney()
{
    firstStop_->addTeekkari(new Teekkari());
    player_->orderFood();

    auto playerBalanceBeforeDelivery = player_->getWalletBalance();
    player_->deliverFood();
    auto playerBalanceAfterDelivery = player_->getWalletBalance();

    QCOMPARE(playerBalanceAfterDelivery > playerBalanceBeforeDelivery, true);
}


QTEST_MAIN(PlayerTest)

#include "PlayerTest.moc"
