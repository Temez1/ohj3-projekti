#include "Kiosk.h"

Kiosk::Kiosk(int foodPrice):
    QGraphicsSvgItem(":/placeholder"),
    food_(Food()),
    foodPrice_(foodPrice)
{
}

Food Kiosk::orderFood()
{
    return food_;
}

int Kiosk::getFoodPrice()
{
    return foodPrice_;
}
