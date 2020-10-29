#include "Game.h"

#include <QDebug>

#include "gameObjects/handlers/BusLineHandler.h"
#include "gameObjects/graphical/Bus.h"
#include "gameObjects/graphical/Stop.h"
#include "gameObjects/graphical/Kiosk.h"

Game::Game(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);

    scene = new QGraphicsScene();
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0,0,1920,1030);
    setScene(scene);

    testMap_ = new QGraphicsSvgItem(":/map");
    scene->addItem(testMap_);

    gameLoopTimer_ = new QTimer(this);
    connect(gameLoopTimer_, &QTimer::timeout, scene, &QGraphicsScene::advance);

    initUI();
    initScene();
    start();
}

void Game::initUI()
{
    jumpAndDropBusButton = new QPushButton("Jump to bus!", this);
    connect(jumpAndDropBusButton, &QPushButton::clicked, this, &Game::jumpAndDropBusButtonClicked);

    orderAndDeliverFoodButton = new QPushButton("Order food", this);
    connect(orderAndDeliverFoodButton, &QPushButton::clicked, this, &Game::orderAndDeliverFoodButtonClicked);
}

void Game::initScene()
{
    // TODO
    // Move to initGame.cpp

    // When using rand, use srand to change seed in each game
    srand(time(0));

    stopLocations_.insert({"keskusta", QPointF(500,300)});
    stopLocations_.insert({"hervanta", QPointF(900,700)});
    stopLocations_.insert({"lentavanniemi", QPointF(200,300)});

    auto kiosk = new Kiosk();

    auto keskusta = new Stop(QString("keskusta"), stopLocations_.at("keskusta"));
    auto hervanta = new Stop(QString("hervanta"), stopLocations_.at("hervanta"));
    auto lentavanniemi = new Stop(QString("lentavanniemi"), stopLocations_.at("lentavanniemi"), kiosk);
    kiosk->setParentItem(lentavanniemi);

    auto stops = {keskusta, hervanta, lentavanniemi};

    scene->addItem(keskusta);
    scene->addItem(hervanta);
    scene->addItem(lentavanniemi);

    // This will create a shared pointer that can be used in multiple busses using the same line
    // Shared pointer gets deleted after last bus using the busline gets deleted
    // i.e. If shared pointer is not used anymore
    auto busline = std::make_shared<BusLineHandler>(BusLineHandler(QString("3"), stops));
    auto bus3a = new Bus(QString("3a"), busline);
    auto bus3b = new Bus(QString("3b"), busline, 2, 1);
    auto bus3a_2 = new Bus(QString("3a"), busline, 2, 2, -1);

    scene->addItem(bus3a);
    scene->addItem(bus3b);
    scene->addItem(bus3a_2);

    QList<Teekkari *> teekkarit;

    for (int i=0; i<INIT_TEEKKARI_AMOUNT; i++) {
        auto teekkari = new Teekkari();
        auto randomStop = *std::next(std::begin(stops), rand()%(stops.size()));
        teekkari->setPos(randomStop->pos());
        scene->addItem(teekkari);
        teekkarit.append(teekkari);
    }
    // END initGame.cpp ?

    teekkariHandler_ = new TeekkariHandler(teekkarit, stops);

    player = new Player("Player name", scene);
    player->setPos(bus3a->pos());
    scene->addItem(player);
}

void Game::start()
{
    gameLoopTimer_->start(16);
}

void Game::jumpAndDropBusButtonClicked()
{
    if ( player->jumpToBus() ){
        jumpAndDropBusButton->setText("Leave the bus!");
        return;
    }

    if ( player->dropFromBus() ){
        jumpAndDropBusButton->setText("Jump to bus!");
        return;
    }
}

void Game::orderAndDeliverFoodButtonClicked()
{
    if ( player->orderFood() ){
        if ( player->isFullOfFood() ){
            orderAndDeliverFoodButton->setText("Deliver food!");
        }
    }
}

void Game::resizeEvent(QResizeEvent *event)
{
    qDebug() << scene->sceneRect();
    qDebug() << this->width() << this->height();
    this->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    resizeButtons();

    QGraphicsView::resizeEvent(event);
}

void Game::resizeButtons()
{
    jumpAndDropBusButton->setGeometry(width() - JUMP_AND_DROP_BUS_BUTTON_WIDTH_PADDING,
                                      height() - JUMP_AND_DROP_BUS_BUTTON_HEIGHT_PADDING,
                                      jumpAndDropBusButton->width(),
                                      jumpAndDropBusButton->height());

    orderAndDeliverFoodButton->setGeometry(width() - ORDER_AND_DELIVER_FOOD_BUTTON_WIDTH_PADDING,
                                           height() - ORDER_AND_DELIVER_FOOD_BUTTON_HEIGHT_PADDING,
                                           orderAndDeliverFoodButton->width(),
                                           orderAndDeliverFoodButton->height());
}
