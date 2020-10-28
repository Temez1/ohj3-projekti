#include "Player.h"
#include <QDebug>

Player::Player(QString name, QGraphicsScene *scene):
    QGraphicsSvgItem(":/player"),
    name_(name),
    scene_(scene),
    currentBus_(nullptr),
    foods_(QList<Food *>())
{
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

    setParentItem(0);
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

Kiosk* Player::searchKioskFromSceneAtCurrentPosition()
{
    auto items = scene_->items(this->pos());
    Kiosk *kiosk = nullptr;

    for (const auto &item : items){
        kiosk = qgraphicsitem_cast<Kiosk *>(item);
        if (kiosk){
            break;
        }
    }
    return kiosk;
}

bool Player::isOnTheBus()
{
    if (currentBus_ == nullptr){
        return false;
    }
    return true;
}

bool Player::orderFood()
{

}

QList<Food *> Player::getFoods()
{
    return foods_;
}
