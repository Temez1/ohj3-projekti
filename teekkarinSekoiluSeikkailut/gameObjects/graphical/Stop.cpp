#include "Stop.h"

#include <QDebug>
#include <QPainter>

Stop::Stop(QString name, QPointF pos, Kiosk *kiosk, QGraphicsItem* parent):
    QGraphicsSvgItem(":/stopSign", parent),
    name_(name),
    kiosk_(kiosk),
    teekkari_(nullptr)
{
    setPos(pos);
}

bool Stop::addKiosk(Kiosk *kiosk)
{
    if ( hasKiosk() ){
        return false;
    }
    kiosk_ = kiosk;
    return true;
}


bool Stop::addTeekkari(Teekkari *teekkari)
{
    if ( hasTeekkari() ){
        return false;
    }
    teekkari_ = teekkari;
    return true;
}

bool Stop::removeTeekkari()
{
    if ( not hasTeekkari() ){
        return false;
    }

    teekkari_ = nullptr;
    return true;
}

QString Stop::getName()
{
    return name_;
}

Kiosk *Stop::getKiosk()
{
    return kiosk_;
}

Teekkari *Stop::getTeekkari()
{
    return teekkari_;
}

bool Stop::hasKiosk()
{
    if ( kiosk_ == nullptr ){
        return false;
    }
    return true;
}

bool Stop::hasTeekkari()
{
    if ( teekkari_ == nullptr ){
        return false;
    }
    return true;
}

QRectF Stop::boundingRect() const
{
    return QRectF(0, -OFFSET_, 58, 92);
}

void Stop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->translate(0,-OFFSET_);
    QGraphicsSvgItem::paint(painter,option,widget);
}

