#ifndef BUS_H
#define BUS_H

#include <QGraphicsRectItem>
#include <QString>
#include <BusLine.h>

class Bus: public QGraphicsRectItem
{
public:
    Bus(QString name, BusLine *busLine, float speed = 2,
        int busLineDirection = 1, int startingStop = 0);
    QString name;
    float speed;

protected:
    void advance(int phase);

private:
    BusLine *busLine_;
    // 1 = From start to end, -1 = From end to start
    int busLineDirection_;
    int nextStop_;
    int lastStop_;

    QPointF pos_;
    QPointF nextStopLocation;
};

#endif // BUS_H
