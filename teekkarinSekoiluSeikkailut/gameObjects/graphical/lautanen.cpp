#include "lautanen.h"


Lautanen::Lautanen(QString name):
    QGraphicsSvgItem(":/pizza"),
    name_(name)
{
    setElementId("foodEmpty_copy");
}

void Lautanen::updateLautanenState( int state)
{
    if (state == EMPTY)
    {
        setElementId("foodEmpty_copy");
        return;
    }
    if (state == HOT)
    {
        setElementId("foodHot_copy");
        return;
    }
    if (state == WARM)
    {
        setElementId("foodWarm_copy");
        return;
    }
    if (state == COLD)
    {
        setElementId("foodCold_copy");
        return;
    }
    else
    {
        return;
    }
}

void Lautanen::playerOrderedFood()
{
    setElementId("foodHot_copy");
    return;
}

void Lautanen::playerDeliveredFood()
{
    setElementId("foodEmpty_copy");
    return;
}
