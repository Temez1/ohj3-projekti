#ifndef KIOSK_H
#define KIOSK_H

#include <QGraphicsSvgItem>

#include "gameObjects/graphical/Food.h"

class Kiosk: public QGraphicsSvgItem
{
public:
    enum { Type = UserType + 4};
    int type() const override { return Type ; }

    Kiosk(int foodPrice, int foodStateChangeTimeInSeconds, int foodPriceFactorModifier);

    Food *orderFood();
    int getFoodPrice();

private:
    const int foodPrice_;
    const int foodStateChangeTimeInSeconds_;
    const int foodPriceFactorModifier_;
};

#endif // KIOSK_H
