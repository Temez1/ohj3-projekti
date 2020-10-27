#ifndef KIOSK_H
#define KIOSK_H

#include <QGraphicsSvgItem>

class Kiosk: public QGraphicsSvgItem
{
public:

    enum { Type = UserType + 4};
    int type() const override { return Type ; }

    Kiosk();
};

#endif // KIOSK_H
