#include "Bus.h"
#include <QBrush>

Bus::Bus(QString name, std::shared_ptr<BusLine> busLine,
         float speed, int startingStop, int busLineDirection) :
    QGraphicsRectItem(),
    name(name),
    busLine_(busLine),
    speed(speed)
{
    std::tie(nextStop_, busLineDirection_) = busLine_->getNextStop(startingStop, busLineDirection);
    setRect(0,0,50,50);
    setBrush(QBrush(Qt::darkCyan, Qt::SolidPattern));
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
