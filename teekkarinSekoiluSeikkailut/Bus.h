#ifndef BUS_H
#define BUS_H

#include <QGraphicsRectItem>
#include <QString>
#include <QVector2D>
#include <BusLine.h>

class Bus: public QGraphicsRectItem
{
public:
    Bus(QString name, std::shared_ptr<BusLine> busLine,
        float speedPixelsPerFrame = 2, int startingStop = 0, int busLineDirection = 1);
    QString name;

    float getSpeedPixelsPerFrame();
    QVector2D getVelocityPixelsPerFrame();

protected:
    void advance(int phase);

private:
    const int BUS_LINE_DIRECTION_FROM_START_TO_END_ = 1;
    const int BUS_LINE_DIRECTION_FROM_END_TO_START_ = -1;

    std::shared_ptr<BusLine> busLine_;
    float speed_;
    int nextStop_;
    int busLineDirection_;
    QVector2D velocity_;
};

#endif // BUS_H
