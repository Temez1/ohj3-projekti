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

    gameLoopTimer_ = new QTimer(this);
    connect(gameLoopTimer_, &QTimer::timeout, scene, &QGraphicsScene::advance);

    this->initScene();
    this->start();
}

void Game::start()
{
    gameLoopTimer_->start(16);
}

void Game::initScene()
{
    stopLocations_.insert({"keskusta", QPointF(500,300)});

    QGraphicsSvgItem *keskusta = new QGraphicsSvgItem(":/stopSign");
    keskusta->setPos(stopLocations_.at("keskusta"));
    scene->addItem(keskusta);
    BusLine *busline = new BusLine(QString("3"));
    busline->addStop(keskusta);

    Bus *bus3a = new Bus(busline, QString("3a"));
    bus3a->setPos(100, 300);
    scene->addItem(bus3a);
}

void Game::resizeEvent(QResizeEvent *event)
{
    qDebug() << scene->sceneRect();
    qDebug() << this->width() << this->height();
    this->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

