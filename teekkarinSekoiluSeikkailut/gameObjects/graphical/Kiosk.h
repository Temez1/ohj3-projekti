#ifndef KIOSK_H
#define KIOSK_H

#include <QGraphicsSvgItem>

#include "gameObjects/graphical/Food.h"

class Kiosk: public QGraphicsSvgItem
{
public:
    enum { Type = UserType + 4};
    int type() const override { return Type ; }

    Kiosk(int foodPrice);

    Food orderFood();
    int getFoodPrice();

private:
    Food food_;
    int foodPrice_;
};

#endif // KIOSK_H
