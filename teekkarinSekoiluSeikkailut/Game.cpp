#include "Game.h"
#include <QDebug>

#include "initScene.h"
#include "gameObjects.h"

Game::Game(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);

    scene = new QGraphicsScene();
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0,0,1920,1030);
    setScene(scene);

    gameLoopTimer_ = new QTimer(this);
    connect(gameLoopTimer_, &QTimer::timeout, scene, &QGraphicsScene::advance);

    mapSeed_ = time(0);

    initUI();
    gameObjects_ = initScene::populateMap(scene, mapSeed_);
    start();
}

void Game::initUI()
{
    jumpAndDropBusButton = new QPushButton("Jump to bus!", this);
    connect(jumpAndDropBusButton, &QPushButton::clicked, this, &Game::jumpAndDropBusButtonClicked);

    orderFoodButton = new QPushButton("Order food", this);
    connect(orderFoodButton, &QPushButton::clicked, this, &Game::orderFoodButtonClicked);

    deliverFoodButton = new QPushButton("Deliver food", this);
    connect(deliverFoodButton, &QPushButton::clicked, this, &Game::deliverFoodButtonClicked);
}

void Game::start()
{
    gameLoopTimer_->start(16);
}

void Game::jumpAndDropBusButtonClicked()
{
    if ( gameObjects_->player->jumpToBus() ){
        jumpAndDropBusButton->setText("Leave the bus!");
        return;
    }

    if ( gameObjects_->player->dropFromBus() ){
        jumpAndDropBusButton->setText("Jump to bus!");
        return;
    }
}

void Game::orderFoodButtonClicked()
{
    gameObjects_->player->orderFood();
}

void Game::deliverFoodButtonClicked()
{
    gameObjects_->player->deliverFood();
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

    orderFoodButton->setGeometry(width() - ORDER_FOOD_BUTTON_WIDTH_PADDING,
                                           height() - ORDER_FOOD_BUTTON_HEIGHT_PADDING,
                                           orderFoodButton->width(),
                                           orderFoodButton->height());

    deliverFoodButton->setGeometry(width() - DELIVER_FOOD_BUTTON_WIDTH_PADDING,
                                           height() - DELIVER_FOOD_BUTTON_HEIGHT_PADDING,
                                           orderFoodButton->width(),
                                           orderFoodButton->height());
}
