#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include "Bus.h"

class Player: public QGraphicsSvgItem
{
public:
    Player(QString name, QGraphicsScene *scene);

    int type() const override { return UserType + 2; }

    bool jumpToBus();
    bool dropFromBus();
    bool isOnTheBus();

    bool orderFood();

private:
    QString name_;
    QGraphicsScene *scene_;
    Bus* currentBus_;

    Bus* searchBusFromSceneAtCurrentPosition();
};

#endif // PLAYER_H
