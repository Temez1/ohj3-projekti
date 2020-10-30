#include "Game.h"
#include <QDebug>

#include "initScene.h"
#include "sceneData.h"

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

    // When using rand, use srand to change seed in each game
    srand(time(0));

    initUI();
    sceneData_ = initScene::populateMap(scene);

    teekkariHandler_ = new TeekkariHandler(sceneData_->teekkarit, sceneData_->stops);

    start();
}

void Game::initUI()
{
    jumpAndDropBusButton = new QPushButton("Jump to bus!", this);
    connect(jumpAndDropBusButton, &QPushButton::clicked, this, &Game::jumpAndDropBusButtonClicked);

    orderAndDeliverFoodButton = new QPushButton("Order food", this);
    connect(orderAndDeliverFoodButton, &QPushButton::clicked, this, &Game::orderAndDeliverFoodButtonClicked);
}

void Game::start()
{
    gameLoopTimer_->start(16);
}

void Game::jumpAndDropBusButtonClicked()
{
    if ( sceneData_->player->jumpToBus() ){
        jumpAndDropBusButton->setText("Leave the bus!");
        return;
    }

    if ( sceneData_->player->dropFromBus() ){
        jumpAndDropBusButton->setText("Jump to bus!");
        return;
    }
}

void Game::orderAndDeliverFoodButtonClicked()
{
    if ( sceneData_->player->orderFood() ){
        if ( sceneData_->player->isFullOfFood() ){
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
