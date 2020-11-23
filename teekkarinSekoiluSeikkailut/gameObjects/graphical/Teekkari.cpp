#include "Teekkari.h"

Teekkari::Teekkari():
    QGraphicsSvgItem(":/teekkari")
{

}

float Teekkari::receiveFood(Food *food)
{
    emit teekkariReceivedFood(this);
    return food->getPrice();
}
