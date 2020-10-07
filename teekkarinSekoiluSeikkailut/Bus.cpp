#include "Bus.h"
#include <QBrush>

Bus::Bus(BusLine *busLine, QString name) :
    QGraphicsRectItem(),
    name(name),
    busLine_(busLine)
{
    setRect(0,0,50,50);
    setBrush(QBrush(Qt::darkCyan, Qt::SolidPattern));
}

void Bus::advance(int phase)
{
    if (phase == 0){
        return;
    }
    this->setPos(this->pos().x() + 1, this->pos().y());
}
