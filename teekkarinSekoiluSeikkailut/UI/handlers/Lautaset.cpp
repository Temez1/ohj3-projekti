#include "Lautaset.h"

Lautaset::Lautaset(int lautasetPadding, QWidget *parent):
    QWidget(parent),
    PADDING_(lautasetPadding)
{

}

void Lautaset::init(int lautanenAmount, Player *player)
{
    for (int i = 0; i < lautanenAmount; ++i) {
        auto lautanen = new Lautanen(this);
        lautanen->move(QPoint(i*PADDING_,0));
        lautaset_.append(lautanen);
    }
    player_ = player;
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
        lautanen->move(lautanen->pos()-QPoint(PADDING_,0));
    }

    auto lautanen = new Lautanen(this);
    lautanen->move(QPoint((lautaset_.length()-1)*PADDING_,0));
}
