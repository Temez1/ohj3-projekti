#include "Bus.h"
#include <QBrush>

Bus::Bus(QString name, std::shared_ptr<BusLine> busLine,
         float speedPixelsPerFrame, int startingStop, int busLineDirection) :
    QGraphicsRectItem(),
    name(name),
    busLine_(busLine),
    speed_(speedPixelsPerFrame)
{
    std::tie(nextStop_, busLineDirection_) = busLine_->getNextStopIndexAndNewDirection(startingStop, busLineDirection);
    velocity_ = QVector2D(0,0);
    setPos(busLine->getStopPosition(startingStop));
    setRect(0,0,50,50);
    setBrush(QBrush(Qt::darkCyan, Qt::SolidPattern));
}

float Bus::getSpeedPixelsPerFrame()
{
    return speed_;
}

QVector2D Bus::getVelocityPixelsPerFrame()
{
    return velocity_;
}

void Bus::advance(int phase)
{
    if (phase == 0){
        return;
    }
    velocity_ = QVector2D(busLine_->getStopPosition(nextStop_) - this->pos()).normalized();
}
