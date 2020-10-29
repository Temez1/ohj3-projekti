#include "Player.h"

#include "Kiosk.h"

Player::Player(QString name, QGraphicsScene *scene):
    QGraphicsSvgItem(":/player"),
    name_(name),
    scene_(scene),
    currentBus_(nullptr),
    foods_(QList<Food>())
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

    for ( const auto &item : items ){
        bus = qgraphicsitem_cast<Bus *>(item);
        if ( bus ){
            break;
        }
    }
    return bus;
}

Stop* Player::searchStopFromSceneAtCurrentPosition()
{
    auto items = scene_->items(this->pos());
    Stop *stop = nullptr;

    for ( const auto &item : items ){
        stop = qgraphicsitem_cast<Stop *>(item);
        if ( stop ){
            break;
        }
    }
    return stop;
}

bool Player::isOnTheBus()
{
    if ( currentBus_ == nullptr ){
        return false;
    }
    return true;
}

bool Player::orderFood()
{
    if ( isFullOfFood() ){
        return false;
    }

    auto stop = searchStopFromSceneAtCurrentPosition();

    if ( not stop ){
        throw std::logic_error("Player is not at stop, shouldn't be possible.");
    }

    Kiosk *kiosk = stop->getKiosk();

    if ( not kiosk ){
        return false;
    }

    auto food = kiosk->orderFood();
    foods_.append(food);
    return true;
}

QList<Food> Player::getFoods()
{
    return foods_;
}

bool Player::isFullOfFood()
{
    if ( foods_.length() == FOOD_MAX_AMOUNT ){
        return true;
    }
    return false;
}
