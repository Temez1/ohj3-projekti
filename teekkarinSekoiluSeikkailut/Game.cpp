#include "Game.h"
#include <QDebug>
#include <QPushButton>

#include "BusLine.h"
#include "Bus.h"
#include "Button.h"
#include "Stop.h"

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
    // TODO
    // Create a helper c++ source file to do all this
    stopLocations_.insert({"keskusta", QPointF(500,300)});
    stopLocations_.insert({"hervanta", QPointF(900,700)});

    auto keskusta = new Stop(QString("keskusta"), stopLocations_.at("keskusta"));
    auto hervanta = new Stop(QString("hervanta"), stopLocations_.at("hervanta"));

    auto stops = {keskusta, hervanta};

    scene->addItem(keskusta);
    scene->addItem(hervanta);

    // This will create a shared pointer that can be used in multiple busses using the same line
    // Shared pointer gets deleted after last bus using the busline gets deleted (If not used somewhere else)
    auto busline = std::make_shared<BusLine>(BusLine(QString("3"), stops));
    auto bus3a = new Bus(QString("3a"), busline);
    auto bus3b = new Bus(QString("3b"), busline);
    bus3a->setPos(100, 300);
    bus3b->setPos(200,300);
    scene->addItem(bus3a);
    scene->addItem(bus3b);
}

void Game::resizeEvent(QResizeEvent *event)
{
    qDebug() << scene->sceneRect();
    qDebug() << this->width() << this->height();
    this->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}
