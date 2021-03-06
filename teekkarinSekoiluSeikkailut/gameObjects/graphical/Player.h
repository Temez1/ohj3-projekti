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
    Player(QString name, QGraphicsScene *scene, Stop* startingStop, int startingMoney,
           int maxFoodAmountToCarry, int cheapestFoodPrice);

    enum { Type = UserType + 2};
    int type() const override { return Type; }

    const int FOOD_MAX_AMOUNT;
    const int CHEAPEST_FOOD_PRICE;

    bool jumpToBus();
    bool dropFromBus();

    bool orderFood();
    bool deliverFood();

    QList<Food*> getFoods();
    Stop* getCurrentStop();
    Wallet* getWallet();


    bool isOnTheBus();
    bool isFullOfFood();
    bool isOutOfFood();

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

signals:
    void playerOutOfMoney();
    void playerOrderedFood(Food *food);
    void playerDeliveredFood(Food *food);

private:
    const QRectF OFFSET_ = QRectF(-42,-75, 0,0);
    QString name_;
    QGraphicsScene *scene_;
    Stop* currentStop_;
    Bus* currentBus_;
    QList<Food*> foods_;
    Wallet *wallet_;

    const int EMPTY = 3;

    Bus* searchBusFromSceneAtCurrentPosition();
};

#endif // PLAYER_H
