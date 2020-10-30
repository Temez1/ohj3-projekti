#include "Stop.h"

Stop::Stop(QString name, QPointF pos, Kiosk *kiosk, QGraphicsItem* parent):
    QGraphicsSvgItem(":/stopSign", parent),
    name_(name),
    kiosk_(kiosk)
{
    setPos(pos);
}

QString Stop::getName()
{
    return name_;
}

Kiosk *Stop::getKiosk()
{
    return kiosk_;
}

