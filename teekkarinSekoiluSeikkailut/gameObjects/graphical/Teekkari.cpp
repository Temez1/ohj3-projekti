#include "Teekkari.h"

Teekkari::Teekkari(Stop *stop):
    QGraphicsSvgItem(":/placeholder"),
    currentStop_(stop)
{

}

unsigned int Teekkari::receiveFood(Food food)
{
    // TODO Return money accordingly to the warmth of the food
    emit teekkariReceivedFood(currentStop_);
    return 15;
}
