#include "Bus.h"
#include <QBrush>

Bus::Bus(QString name, std::shared_ptr<BusLineHandler> busLineHandler,
         float speedPixelsPerFrame, int startingStop, int busLineDirection, int busStopWaitTimeInMilliseconds) :
    QGraphicsRectItem(),
    name_(name),
    busLineHandler_(busLineHandler),
    speed_(speedPixelsPerFrame),
    busStopWaitTimeMilliseconds_(busStopWaitTimeInMilliseconds)
{
    currentStop_ = busLineHandler_->getStopByIndex(startingStop);
    std::tie(nextStopIndex_, busLineDirection_) = busLineHandler_->getNextStopIndexAndNewDirection(startingStop, busLineDirection);
    velocity_ = QVector2D(0,0);
    busWaitTimer_ = new QTimer(this);
    connect(busWaitTimer_, &QTimer::timeout, this, &Bus::busWaitTimerOnTimeout);
    isWaitingAtStop_ = false;

    setPos(busLineHandler->getStopPosition(startingStop));
    setRect(-25,-25,50,50);
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

Stop *Bus::getCurrentStop()
{
    return currentStop_;
}

bool Bus::isWaitingAtStop()
{
    return isWaitingAtStop_;
}

void Bus::advance(int phase)
{
    if (phase == 0){
        return;
    }

    if ( isWaitingAtStop_ ){
        return;
    }

    if ( QVector2D(busLineHandler_->getStopPosition(nextStopIndex_) - this->pos()).length() < speed_ ){
        currentStop_ = busLineHandler_->getStopByIndex(nextStopIndex_);
        std::tie(nextStopIndex_, busLineDirection_) = busLineHandler_->getNextStopIndexAndNewDirection(nextStopIndex_, busLineDirection_);
        isWaitingAtStop_ = true;
        busWaitTimer_->start(busStopWaitTimeMilliseconds_);
        return;
    }

    velocity_ = (QVector2D(busLineHandler_->getStopPosition(nextStopIndex_) - this->pos()).normalized()) * speed_;
    setPos(this->pos() + velocity_.toPointF());
}

void Bus::busWaitTimerOnTimeout()
{
    isWaitingAtStop_ = false;
    currentStop_ = nullptr;
}
