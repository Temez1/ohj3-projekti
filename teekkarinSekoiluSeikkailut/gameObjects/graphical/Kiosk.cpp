#include "Kiosk.h"

Kiosk::Kiosk(Food food):
    QGraphicsSvgItem(":/placeholder"),
    food_(food)
{
}

Food Kiosk::orderFood()
{
    return food_;
}

int Kiosk::getFoodPrice()
{
    return food_.getPrice();
}
