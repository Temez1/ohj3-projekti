#include "Player.h"
#include <QDebug>

#include "Kiosk.h"
#include "gameObjects/graphical/lautanen.h"

Player::Player(QString name, QGraphicsScene *scene, Stop* startingStop, int startingMoney, int maxFoodAmountToCarry):
    QGraphicsSvgItem(":/player"),
    FOOD_MAX_AMOUNT(maxFoodAmountToCarry),
    name_(name),
    scene_(scene),
    currentStop_(startingStop),
    currentBus_(nullptr),
    foods_(QList<Food*>()),
    wallet_(new Wallet(startingMoney))
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

    Kiosk *kiosk = currentStop_->getKiosk();

    if ( not kiosk ){
        return false;
    }

    if ( not wallet_->pay(kiosk->getFoodPrice())){
        emit playerOutOfMoney();
        return false;
    }

    auto food = kiosk->orderFood();
    foods_.append(food);
    qDebug() << "Player ordered food";
    qDebug() << "Balance" << getWalletBalance();
    emit playerOrderedFood();
    return true;
}

bool Player::deliverFood()
{
    if ( isOutOfFood() ){
        return false;
    }

    if ( isOnTheBus() ){
        return false;
    }

    auto food = foods_.takeFirst();

    if ( currentStop_->hasTeekkari() ){
        auto teekkari = currentStop_->getTeekkari();
        auto money = teekkari->receiveFood(food);
        wallet_->receive(money);

        qDebug() << "Player delivered food to teekkari";
        qDebug() << "Balance" << getWalletBalance();
    }

    emit playerDeliveredFood();
    return true;
}

QList<Food*> Player::getFoods()
{
    return foods_;
}

Stop *Player::getCurrentStop()
{
    return currentStop_;
}

int Player::getWalletBalance()
{
    return wallet_->getBalance();
}

bool Player::isOnTheBus()
{
    if ( currentBus_ == nullptr ){
        if ( currentStop_ == nullptr ){
            throw std::logic_error("If player is not on the bus, player should be at stop!");
        }
        return false;
    }
    if ( currentStop_ != nullptr ){
        throw std::logic_error("If player is on the bus, player should not be at stop!");
    }
    return true;
}

bool Player::isFullOfFood()
{
    if ( foods_.length() == FOOD_MAX_AMOUNT ){
        qDebug() << "Player is full of food";
        return true;
    }
    qDebug() << "Player is not full of food. Player has" << foods_.length() << "food(s)";
    return false;
}

bool Player::isOutOfFood()
{
    if ( foods_.empty() ){
        qDebug() << "Player is out of food";
        return true;
    }
    qDebug() << "Player is not out of food";
    return false;
}
