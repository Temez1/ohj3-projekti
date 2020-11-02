#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsScene>
#include <QGraphicsSvgItem>

#include "Bus.h"
#include "Food.h"
#include "Stop.h"
#include "gameObjects/Wallet.h"

class Player: public QGraphicsSvgItem
{ Q_OBJECT
public:
    Player(QString name, QGraphicsScene *scene, Stop* startingStop, int startingMoney, int maxFoodAmountToCarry);

    enum { Type = UserType + 2};
    int type() const override { return Type; }

    const int FOOD_MAX_AMOUNT;

    bool jumpToBus();
    bool dropFromBus();

    bool orderFood();
    bool deliverFood();
    QList<Food> getFoods();

    bool isOnTheBus();
    bool isFullOfFood();

signals:
    void playerOutOfMoney();
    void playerOrderedFood();

private:
    QString name_;
    QGraphicsScene *scene_;
    Stop* currentStop_;
    Bus* currentBus_;
    QList<Food> foods_;
    Wallet wallet_;

    Bus* searchBusFromSceneAtCurrentPosition();
};

#endif // PLAYER_H
