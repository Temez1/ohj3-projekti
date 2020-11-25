#include "Bus.h"

#include <QDebug>
#include <QPainter>

Bus::Bus(QString name, std::shared_ptr<BusLine> busLine, float DEFAULT_SPEED,
         float speedPixelsPerFrame, int startingStop, int busLineDirection, int busStopWaitTimeInMilliseconds) :
    QGraphicsSvgItem(":/buss"),
    DEFAULT_SPEED_(DEFAULT_SPEED),
    name_(name),
    busLine_(busLine),
    speed_(speedPixelsPerFrame),
    busStopWaitTimeMilliseconds_(busStopWaitTimeInMilliseconds)
{

    currentStop_ = busLine_->getStopByIndex(startingStop);
    std::tie(nextStopIndex_, busLineDirection_) = busLine_->getNextStopIndexAndNewDirection(startingStop, busLineDirection);
    velocity_ = QVector2D(0,0);
    busWaitTimer_ = new QTimer(this);
    connect(busWaitTimer_, &QTimer::timeout, this, &Bus::busWaitTimerOnTimeout);
    isWaitingAtStop_ = false;

    setPos(busLine_->getStopPosition(startingStop));
    updateGraphics();
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

    if ( QVector2D(busLine_->getStopPosition(nextStopIndex_) - this->pos()).length() < speed_ ){
        currentStop_ = busLine_->getStopByIndex(nextStopIndex_);
        std::tie(nextStopIndex_, busLineDirection_) = busLine_->getNextStopIndexAndNewDirection(nextStopIndex_, busLineDirection_);
        isWaitingAtStop_ = true;
        updateVelocity();
        updateGraphics();
        busWaitTimer_->start(busStopWaitTimeMilliseconds_);
        return;
    }

    updateVelocity();
    setPos(this->pos() + velocity_.toPointF());
}

QRectF Bus::boundingRect() const
{
    return QRectF(OFFSET_.x(), OFFSET_.y(), 84.8483, 55.5828);
}

void Bus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->translate(OFFSET_.x(),OFFSET_.y());
    QGraphicsSvgItem::paint(painter,option,widget);
}

void Bus::updateVelocity()
{
    velocity_ = (QVector2D(busLine_->getStopPosition(nextStopIndex_) - this->pos()).normalized()) * speed_;
}

void Bus::updateGraphics()
{
    if ( velocity_.x() >= 0 ){
        if ( speed_ > DEFAULT_SPEED_ + 0.7 ){
            setElementId(name_+"_fast"+"_E");
        }
        else {
            setElementId(name_+"_E");
        }
        return;
    }

    if ( velocity_.x() < 0 ){
        if ( speed_ > DEFAULT_SPEED_ + 0.7 ){
            setElementId(name_+"_fast"+"_W");
        }
        else {
            setElementId(name_+"_W");
        }
    }
}

void Bus::busWaitTimerOnTimeout()
{
    isWaitingAtStop_ = false;
    currentStop_ = nullptr;
}
