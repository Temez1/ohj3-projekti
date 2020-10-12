#include "Stop.h"

Stop::Stop(QString name, QPointF pos, QGraphicsItem* parent):
    QGraphicsSvgItem(":/stopSign", parent),
    name_(name)
{
    setPos(pos);
}
