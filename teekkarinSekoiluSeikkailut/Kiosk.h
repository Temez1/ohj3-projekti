#ifndef KIOSK_H
#define KIOSK_H

#include <QGraphicsSvgItem>

#include "Food.h"

class Kiosk: public QGraphicsSvgItem
{
public:

    enum { Type = UserType + 4};
    int type() const override { return Type ; }

    Kiosk();
    Food orderFood();

private:
    Food food_;
};

#endif // KIOSK_H
