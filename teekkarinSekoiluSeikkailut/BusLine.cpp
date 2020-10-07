#include "BusLine.h"

BusLine::BusLine(QString name):
    name(name)
{
}

void BusLine::addStop(QGraphicsSvgItem *stop)
{
    stops_.push_back(stop);
}
