#include "Kiosk.h"

Kiosk::Kiosk(int foodPrice, int foodStateChangeTimeInSeconds, int foodPriceFactorModifier):
    QGraphicsSvgItem(":/grill"),
    foodPrice_(foodPrice),
    foodStateChangeTimeInSeconds_(foodStateChangeTimeInSeconds),
    foodPriceFactorModifier_(foodPriceFactorModifier)
{

}

Food *Kiosk::orderFood()
{
    return new Food(foodPrice_, foodStateChangeTimeInSeconds_, foodPriceFactorModifier_);
}

int Kiosk::getFoodPrice()
{
    return foodPrice_;
}
