#include "Food.h"

Food::Food(int price, int foodStateChangeTimeInSeconds, int foodPriceFactorModifier):
    FOOD_PRICE_FACTOR_MODIFIER(foodPriceFactorModifier),
    price_(price),
    foodStateChangeTimeInSeconds_(foodStateChangeTimeInSeconds)
{
    state_ = HOT;
    QTimer *foodStateTimer_ = new QTimer(this);
    connect(foodStateTimer_, &QTimer::timeout, this, &Food::foodStateTimeout);

    foodStateTimer_->start(foodStateChangeTimeInSeconds_*1000);
}

Food::~Food()
{

}

int Food::getPrice()
{
    return price_ * (state_ + FOOD_PRICE_FACTOR_MODIFIER);
}

int Food::getState()
{
    return state_;
}

void Food::foodStateTimeout()
{
    if (state_ == COLD)
    {
        return;
    }
    state_ -=1;
    emit foodStateChanged(state_);

}

