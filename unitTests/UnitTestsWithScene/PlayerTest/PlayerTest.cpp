#include <QtTest>
#include <QCoreApplication>
#include <QGraphicsScene>

#include "Player.h"
#include "Bus.h"

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

    void Scenario_PlayerIsOnTheBusAndSceneAdvances_PlayerPosEqualsBusPos();

private:
    QGraphicsScene *scene_;
    Player *player_;
    Stop *firstStop_;
    Stop *secondStop_;
    std::shared_ptr<BusLine> busline_;
    Bus *bus_;
    const float BUS_DEFAULT_SPEED_;
    const int FIRST_STOP_INDEX = 0;
    const int SECOND_STOP_INDEX = 1;
    const int BUS_DIRECTION_FROM_START_TO_END_ = 1;
    const int BUS_DIRECTION_FROM_END_TO_START_ = -1;
};

PlayerTest::PlayerTest():
    scene_(new QGraphicsScene()),
    player_(new Player("Test", scene_)),
    firstStop_(new Stop(QString("testStop1"), QPointF(100,100))),
    secondStop_(new Stop(QString("testStop2"), QPointF(200,100))),
    busline_(std::make_shared<BusLine>(BusLine("Test busline", {firstStop_, secondStop_}))),
    bus_(new Bus("Test Bus", busline_)),
    BUS_DEFAULT_SPEED_(bus_->getSpeedPixelsPerFrame())
{}

PlayerTest::~PlayerTest()
{}

void PlayerTest::init()
{
    firstStop_ = new Stop(QString("testStop1"), QPointF(100,100));
    secondStop_ = new Stop(QString("testStop2"), QPointF(200,100));

    busline_ = std::make_shared<BusLine>(BusLine("Test busline", {firstStop_, secondStop_}));
    bus_ = new Bus("Test Bus", busline_);

    scene_ = new QGraphicsScene();
    scene_->addItem(firstStop_);
    scene_->addItem(secondStop_);
    scene_->addItem(bus_);

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

void PlayerTest::Scenario_PlayerIsOnTheBusAndSceneAdvances_PlayerPosEqualsBusPos()
{
    player_->setPos(bus_->pos());
    player_->jumpToBus();

    scene_->advance();
    auto playerParentPos = player_->parentItem()->pos();

    QCOMPARE(playerParentPos, bus_->pos());
}


QTEST_MAIN(PlayerTest)

#include "PlayerTest.moc"
