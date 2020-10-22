#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "Bus.h"

class Player: public QGraphicsRectItem
{
public:
    Player(QString name, QGraphicsScene *scene);

    enum { Type = UserType + 2};
    int type() const override { return Type; }

    bool jumpToBus();
    bool dropFromBus();
    bool isOnTheBus();

private:
    QString name_;
    QGraphicsScene *scene_;
    Bus* currentBus_;

    Bus* searchBusFromSceneAtCurrentPosition();
};

#endif // PLAYER_H
