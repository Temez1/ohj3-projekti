#include "Player.h"
#include "Bus.h"
#include <QDebug>

Player::Player(QGraphicsScene *scene):
    scene_(scene),
    isOnTheBus_(false)
{
    setRect(0,0,20,20);
    setBrush(QBrush(Qt::black, Qt::SolidPattern));
}

bool Player::jumpToBus()
{
    if (isOnTheBus_){
        return false;
    }

    auto items = scene_->items(this->pos());

    Bus *bus = nullptr;
    for (const auto &item : items){
        bus = qgraphicsitem_cast<Bus *>(item);
        qDebug() << bus;
    }

    if ( items.isEmpty() ){
        return false;
    }

    isOnTheBus_ = true;
    //setParentItem(items.first());
    return true;
}

bool Player::isOnTheBus()
{
    return isOnTheBus_;
}
