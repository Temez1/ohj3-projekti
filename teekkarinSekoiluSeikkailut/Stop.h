#ifndef STOP_H
#define STOP_H

#include <QGraphicsSvgItem>

class Stop: public QGraphicsSvgItem
{
public:
    Stop(QString name, QPointF pos, QGraphicsItem* parent=NULL);

private:
    QString name_;
};

#endif // STOP_H
