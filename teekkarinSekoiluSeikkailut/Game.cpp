#include "Game.h"

Game::Game(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene();
    setScene(scene);



    testMap_ = new QGraphicsSvgItem(":/map");
    scene->addItem(testMap_);




    busLines = new BusLines();
    testButton_ = new Button("Hi, press me to exit!");
    connect(testButton_, &Button::clicked, this, &Game::close);
    scene->addItem(testButton_);
}
