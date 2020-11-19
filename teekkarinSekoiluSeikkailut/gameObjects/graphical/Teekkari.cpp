#include "Teekkari.h"

Teekkari::Teekkari():
    QGraphicsSvgItem(":/teekkari")
{

}

unsigned int Teekkari::receiveFood(Food *food)
{
    emit teekkariReceivedFood(this);
    return food->getPrice();
}
