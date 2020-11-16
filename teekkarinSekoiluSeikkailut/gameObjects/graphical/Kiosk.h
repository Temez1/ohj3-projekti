#ifndef KIOSK_H
#define KIOSK_H

#include <QGraphicsSvgItem>

#include "gameObjects/graphical/Food.h"

class Kiosk: public QGraphicsSvgItem
{
public:
    enum { Type = UserType + 4};
    int type() const override { return Type ; }

    Kiosk(int foodPrice, int foodStateChangeTimeInSeconds);

    Food *orderFood();
    int getFoodPrice();

private:
    int foodPrice_;
    int foodStateChangeTimeInSeconds_;
};

#endif // KIOSK_H
