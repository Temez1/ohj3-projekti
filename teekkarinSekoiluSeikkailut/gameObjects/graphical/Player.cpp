#include "Player.h"
#include <QDebug>
#include <QPainter>

#include "Kiosk.h"

Player::Player(QString name, QGraphicsScene *scene, Stop* startingStop, int startingMoney,
               int maxFoodAmountToCarry, int cheapestFoodPrice):
    QGraphicsSvgItem(":/player"),
    FOOD_MAX_AMOUNT(maxFoodAmountToCarry),
    CHEAPEST_FOOD_PRICE(cheapestFoodPrice),
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
        return false;
    }

    auto food = kiosk->orderFood();
    foods_.append(food);
    qDebug() << "Player ordered food";
    emit playerOrderedFood(food);
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
        wallet_->receive(static_cast<unsigned int>(money));

        qDebug() << "Player delivered food to teekkari";
    }

    if ( (wallet_->getBalance() < CHEAPEST_FOOD_PRICE) and isOutOfFood() ){
        emit playerOutOfMoney();
    }

    emit playerDeliveredFood(food);
    delete food;
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

Wallet *Player::getWallet()
{
    return wallet_;
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

QRectF Player::boundingRect() const
{
    return QRectF(OFFSET_.x(), OFFSET_.y(), 84, 106);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->translate(OFFSET_.x(),OFFSET_.y());
    QGraphicsSvgItem::paint(painter,option,widget);
}


