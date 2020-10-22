#include "Player.h"
#include <QDebug>

Player::Player(QString name, QGraphicsScene *scene):
    name_(name),
    scene_(scene),
    isOnTheBus_(false)
{
    setRect(-10,-10,20,20);
    setBrush(QBrush(Qt::black, Qt::SolidPattern));
}

bool Player::jumpToBus()
{
    if (isOnTheBus_){
        return false;
    }

    auto bus = searchBusFromSceneAtCurrentPosition();

    if ( not bus ){
        return false;
    }

    isOnTheBus_ = true;
    setPos(0,0);
    setParentItem(bus);
    return true;
}

Bus* Player::searchBusFromSceneAtCurrentPosition()
{
    auto items = scene_->items(this->pos());
    Bus *bus = nullptr;

    for (const auto &item : items){
        bus = qgraphicsitem_cast<Bus *>(item);
        if (bus){
            break;
        }
    }
    return bus;
}

bool Player::isOnTheBus()
{
    return isOnTheBus_;
}
