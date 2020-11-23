#include "lautanen.h"

Lautanen::Lautanen(QString name):
    QGraphicsSvgItem(":/pizza"),
    name_(name)
{

}

void Lautanen::updateLautanenState(int state)
{
    if (state == EMPTY)
    {
        setElementId("foodEmpty copy");
        return;
    }
    if (state == HOT)
    {
        setElementId("foodHot copy");
        return;
    }
    if (state == WARM)
    {
        setElementId("foodWarm copy");
        return;
    }
    if (state == COLD)
    {
        setElementId("foodCold copy");
        return;
    }
    else
    {
        return;
    }
}
