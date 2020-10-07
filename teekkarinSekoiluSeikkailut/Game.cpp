#include "Game.h"
#include <QDebug>
#include <QPushButton>

Game::Game(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);

    scene = new QGraphicsScene();
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0,0,1920,1080);
    setScene(scene);

    testMap_ = new QGraphicsSvgItem(":/map");
    scene->addItem(testMap_);

    busLines = new BusLines();

    QPushButton *button1 = new QPushButton("Text", this);

    testButton_ = new Button("Hi, press me to exit!");
    testButton_->setPos(0,200);
    connect(testButton_, &Button::clicked, this, &Game::close);
    scene->addItem(testButton_);

    startButton_ = new Button("Hi, press me to start!");
    connect(startButton_, &Button::clicked, this, &Game::start);
    startButton_->setPos(100,100);
    scene->addItem(startButton_);

    gameLoopTimer_ = new QTimer(this);
    connect(gameLoopTimer_, &QTimer::timeout, scene, &QGraphicsScene::advance);
}

void Game::start()
{
    gameLoopTimer_->start(16);
}

void Game::resizeEvent(QResizeEvent *event)
{
    qDebug() << scene->sceneRect();
    qDebug() << this->width() << this->height();
    testButton_->setPos(this->mapToScene(this->width() - 250, this->height() - 100));
    this->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

