#include "Teekkari.h"

Teekkari::Teekkari():
    QGraphicsSvgItem(":/placeholder")
{

}

unsigned int Teekkari::receiveFood(Food food)
{
    // TODO Return money accordingly to the warmth of the food
    emit teekkariReceivedFood(this);
    return 15;
}
