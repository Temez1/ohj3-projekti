#include "Lautaset.h"

#include <QDebug>

Lautaset::Lautaset(int lautasetPadding, QWidget *parent):
    QWidget(parent),
    PADDING_(lautasetPadding)
{

}

void Lautaset::init(int lautanenAmount, Player *player)
{
    LAUTANEN_AMOUNT_ = lautanenAmount;

    for (int i = 0; i < lautanenAmount; ++i) {
        auto lautanen = new Lautanen(this);
        lautanen->move(QPoint(i*(lautanen->width()+PADDING_),0));
        lautaset_.append(lautanen);
    }

    connect(player, &Player::playerOrderedFood, this, &Lautaset::playerOrderedFood);
    connect(player, &Player::playerDeliveredFood, this, &Lautaset::playerDeliveredFood);

    player_ = player;

    setGeometry(childrenRect());
}

void Lautaset::playerOrderedFood(Food *food)
{
    auto indexOfFood = player_->getFoods().length() - 1;
    auto lautanen = lautaset_.at(indexOfFood);
    lautanen->addFood();
    connect(food, &Food::foodStateChanged, lautanen, &Lautanen::updateLautanenState);
}

void Lautaset::playerDeliveredFood(Food *food)
{
    auto firstLautanen = lautaset_.takeFirst();
    delete firstLautanen;

    for (auto &lautanen: lautaset_){
        lautanen->move(lautanen->pos()-QPoint(lautanen->width()+PADDING_,0));
    }

    auto lautanen = new Lautanen(this);
    lautanen->move(QPoint((LAUTANEN_AMOUNT_ - 1)*(lautanen->width()+PADDING_),0));
    lautaset_.append(lautanen);
    lautanen->show();
}
