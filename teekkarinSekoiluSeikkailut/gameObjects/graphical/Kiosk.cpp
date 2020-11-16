#include "Kiosk.h"

Kiosk::Kiosk(int foodPrice, int foodStateChangeTimeInSeconds):
    QGraphicsSvgItem(":/placeholder"),
    foodPrice_(foodPrice),
    foodStateChangeTimeInSeconds_(foodStateChangeTimeInSeconds)
{

}

Food *Kiosk::orderFood()
{
    return new Food(foodPrice_, foodStateChangeTimeInSeconds_);
}

int Kiosk::getFoodPrice()
{
    return foodPrice_;
}
