
#include "Game.h"

Game::Game(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene();
    setScene(scene);

    testMap_ = new QGraphicsSvgItem(":/test");
    scene->addItem(testMap_);

    busLines = new BusLines();
}
