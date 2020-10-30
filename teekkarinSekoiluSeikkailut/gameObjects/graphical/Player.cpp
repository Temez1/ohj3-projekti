#include "Player.h"
#include <QDebug>

#include "Kiosk.h"

Player::Player(QString name, QGraphicsScene *scene, Stop* startingStop, int startingMoney):
    QGraphicsSvgItem(":/player"),
    name_(name),
    scene_(scene),
    currentStop_(startingStop),
    currentBus_(nullptr),
    foods_(QList<Food>()),
    wallet_(Wallet(startingMoney))
{
    setPos(startingStop->pos());
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

    currentStop_ = nullptr;
    currentBus_ = bus;
    setPos(0,0);
    setParentItem(bus);
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

bool Player::dropFromBus()
{
    if ( not isOnTheBus() ){
        return false;
    }

    if ( not currentBus_->isWaitingAtStop() ){
        return false;
    }

    currentStop_ = currentBus_->getCurrentStop();

    if ( not isAtStop() ){
        throw std::logic_error("If player dropped from bus, player should be at stop!");
    }

    setParentItem(0);
    setPos(currentBus_->pos());
    currentBus_ = nullptr;
    return true;
}

bool Player::orderFood()
{
    if ( isFullOfFood() ){
        return false;
    }

    if ( isOnTheBus() ){
        return false;
    }

    if ( not isAtStop() ){
        throw std::logic_error("If player is not on the bus, player should be at stop!");
    }

    Kiosk *kiosk = currentStop_->getKiosk();

    if ( not kiosk ){
        return false;
    }

    if ( not wallet_.pay(kiosk->getFoodPrice())){
        emit playerOutOfMoney();
        return false;
    }

    auto food = kiosk->orderFood();
    emit playerOrderedFood();
    foods_.append(food);
    return true;
}

QList<Food> Player::getFoods()
{
    return foods_;
}

bool Player::isOnTheBus()
{
    if ( currentBus_ == nullptr ){
        return false;
    }
    return true;
}

bool Player::isAtStop()
{
    if ( currentStop_ == nullptr ){
        return false;
    }
    return true;
}

bool Player::isFullOfFood()
{
    if ( foods_.length() == FOOD_MAX_AMOUNT ){
        return true;
    }
    return false;
}
