#include "Stop.h"

Stop::Stop(QString name, QPointF pos, Kiosk *kiosk, QGraphicsItem* parent):
    QGraphicsSvgItem(":/stopSign", parent),
    name_(name),
    kiosk_(kiosk),
    teekkari_(nullptr)
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

bool Stop::hasTeekkari()
{
    if ( teekkari_ == nullptr ){
        return false;
    }
    return true;
}

