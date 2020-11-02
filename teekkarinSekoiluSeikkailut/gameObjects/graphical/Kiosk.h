#ifndef KIOSK_H
#define KIOSK_H

#include <QGraphicsSvgItem>

#include "gameObjects/graphical/Food.h"

class Kiosk: public QGraphicsSvgItem
{
public:
    enum { Type = UserType + 4};
    int type() const override { return Type ; }

    Kiosk(Food food);

    Food orderFood();
    int getFoodPrice();

private:
    Food food_;
};

#endif // KIOSK_H
