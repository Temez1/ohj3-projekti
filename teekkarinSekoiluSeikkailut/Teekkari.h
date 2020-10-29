#ifndef TEEKKARI_H
#define TEEKKARI_H

#include <QGraphicsSvgItem>

#include "Food.h"

class Teekkari : public QGraphicsSvgItem
{
public:
    Teekkari();

    int receiveFood(Food food);
};

#endif // TEEKKARI_H
