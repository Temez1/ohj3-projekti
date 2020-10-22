#ifndef STOP_H
#define STOP_H

#include <QGraphicsSvgItem>

class Stop: public QGraphicsSvgItem
{
public:
    Stop(QString name, QPointF pos, QGraphicsItem* parent=NULL);

    enum { Type = UserType + 3};
    int type() const override { return Type; }

private:
    QString name_;
};

#endif // STOP_H
