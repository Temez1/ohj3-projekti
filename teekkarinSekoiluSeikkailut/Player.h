#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsScene>
#include <QGraphicsSvgItem>

#include "Bus.h"
#include "Food.h"
#include "Kiosk.h"

class Player: public QGraphicsSvgItem
{
public:
    Player(QString name, QGraphicsScene *scene);

    enum { Type = UserType + 2};
    int type() const override { return Type; }

    bool jumpToBus();
    bool dropFromBus();
    bool isOnTheBus();

    bool orderFood();
    QList<Food *> getFoods();

private:
    QString name_;
    QGraphicsScene *scene_;
    Bus* currentBus_;
    QList<Food *> foods_;

    Bus* searchBusFromSceneAtCurrentPosition();
    Kiosk* searchKioskFromSceneAtCurrentPosition();
};

#endif // PLAYER_H
