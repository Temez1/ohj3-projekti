#include "Kiosk.h"

Kiosk::Kiosk():
    QGraphicsSvgItem(":/placeholder"),
    food_(Food())
{
}

Food Kiosk::orderFood()
{
    return food_;
}
