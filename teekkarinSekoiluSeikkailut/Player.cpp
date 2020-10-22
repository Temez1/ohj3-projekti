#include "Player.h"
#include <QDebug>

Player::Player(QString name, QGraphicsScene *scene):
    name_(name),
    scene_(scene),
    currentBus_(nullptr)
{
    setRect(-10,-10,20,20);
    setBrush(QBrush(Qt::black, Qt::SolidPattern));
}

bool Player::jumpToBus()
{
    if ( isOnTheBus() ){
        return false;
    }

    auto bus = searchBusFromSceneAtCurrentPosition();

    if ( not bus ){
        return false;
    }

    currentBus_ = bus;
    setPos(0,0);
    setParentItem(bus);
    return true;
}

bool Player::dropFromBus()
{
    if ( not isOnTheBus() ){
        return false;
    }

    if ( not currentBus_->isWaitingAtStop() ){
        return false;
    }

    setPos(currentBus_->pos());
    currentBus_ = nullptr;
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
    if (currentBus_ == nullptr){
        return false;
    }
    return true;
}
