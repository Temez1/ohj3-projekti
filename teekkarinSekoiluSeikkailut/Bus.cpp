#include "Bus.h"
#include <QBrush>

Bus::Bus(QString name, std::shared_ptr<BusLine> busLine,
         float speedPixelsPerFrame, int startingStop, int busLineDirection, int busStopWaitTimeInMilliseconds) :
    QGraphicsRectItem(),
    name(name),
    busLine_(busLine),
    speed_(speedPixelsPerFrame),
    busStopWaitTimeMilliseconds_(busStopWaitTimeInMilliseconds)
{
    std::tie(nextStopIndex_, busLineDirection_) = busLine_->getNextStopIndexAndNewDirection(startingStop, busLineDirection);
    velocity_ = QVector2D(0,0);
    busWaitTimer_ = new QTimer(this);
    connect(busWaitTimer_, &QTimer::timeout, this, &Bus::busWaitTimerOnTimeout);
    isWaitingAtStop_ = false;

    setPos(busLine->getStopPosition(startingStop));
    setRect(0,0,50,50);
    setBrush(QBrush(Qt::darkCyan, Qt::SolidPattern));
}

Bus::~Bus()
{

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

    if ( isWaitingAtStop_ ){
        return;
    }

    if ( QVector2D(busLine_->getStopPosition(nextStopIndex_) - this->pos()).length() < speed_ ){
        std::tie(nextStopIndex_, busLineDirection_) = busLine_->getNextStopIndexAndNewDirection(nextStopIndex_, busLineDirection_);
        isWaitingAtStop_ = true;
        busWaitTimer_->start(busStopWaitTimeMilliseconds_);
        return;
    }

    velocity_ = (QVector2D(busLine_->getStopPosition(nextStopIndex_) - this->pos()).normalized()) * speed_;
    setPos(this->pos() + velocity_.toPointF());
}

void Bus::busWaitTimerOnTimeout()
{
    isWaitingAtStop_ = false;
}
