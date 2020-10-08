#include "Bus.h"
#include <QBrush>

Bus::Bus(QString name, BusLine *busLine, float speed,
         int busLineDirection, int startingStop) :
    QGraphicsRectItem(),
    name(name),
    speed(speed),
    busLine_(busLine),
    busLineDirection_(busLineDirection)
{
    // busLine->getNextStop(startingStop, )
    setRect(0,0,50,50);
    setBrush(QBrush(Qt::darkCyan, Qt::SolidPattern));
    pos_ = QPointF(0,0);
}

void Bus::advance(int phase)
{
    if (phase == 0){
        return;
    }
    // have I arrived at next stop?
//    pos_ = this->pos();

//    if (pos_ )
    // Yes -> Get me next stop
    // No -> Keep moving towards next stop
}
