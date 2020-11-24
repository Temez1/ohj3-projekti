#include "Teekkari.h"

#include <QPainter>
#include <QDebug>

Teekkari::Teekkari():
    QGraphicsSvgItem(":/teekkari")
{
}

float Teekkari::receiveFood(Food *food)
{
    emit teekkariReceivedFood(this);
    return food->getPrice();
}

QRectF Teekkari::boundingRect() const
{
    return QRectF(OFFSET_.x(), OFFSET_.y(), 134, 115);
}

void Teekkari::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->translate(OFFSET_.x(),OFFSET_.y());
    QGraphicsSvgItem::paint(painter,option,widget);
}
