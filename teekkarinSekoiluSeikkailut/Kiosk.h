#ifndef KIOSK_H
#define KIOSK_H

#include <QGraphicsSvgItem>

class Kiosk: public QGraphicsSvgItem
{
public:

    int type() const override { return UserType + 4 ; }

    Kiosk();
};

#endif // KIOSK_H
