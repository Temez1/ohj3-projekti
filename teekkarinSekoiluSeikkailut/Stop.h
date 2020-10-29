#ifndef STOP_H
#define STOP_H

#include <QGraphicsSvgItem>

#include "Kiosk.h"

class Stop: public QGraphicsSvgItem
{
public:
    Stop(QString name, QPointF pos, Kiosk *kiosk=nullptr, QGraphicsItem* parent=NULL);

    enum { Type = UserType + 3};
    int type() const override { return Type; }

    Kiosk *getKiosk();

private:
    QString name_;
    Kiosk *kiosk_;
};

#endif // STOP_H
