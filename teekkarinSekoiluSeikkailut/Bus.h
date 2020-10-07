#ifndef BUS_H
#define BUS_H

#include <QGraphicsRectItem>
#include <QString>
#include <BusLine.h>

class Bus: public QGraphicsRectItem
{
public:
    Bus(BusLine *busLine, QString name);
    QString name;

protected:
    void advance(int phase);

private:
    BusLine *busLine_;
};

#endif // BUS_H
