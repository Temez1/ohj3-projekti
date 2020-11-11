#ifndef BUS_H
#define BUS_H

#include <QGraphicsSvgItem>
#include <QString>
#include <QVector2D>
#include <QTimer>

#include "gameObjects/BusLine.h"
#include "gameObjects/graphical/Stop.h"

class Bus: public QGraphicsSvgItem
{
    Q_OBJECT
public:
    Bus(QString name, std::shared_ptr<BusLine> busLine, float speedPixelsPerFrame = 2, int startingStop = 0,
        int busLineDirection = 1, int busStopWaitTimeInMilliseconds = 2000);
    ~Bus();

    enum { Type = UserType + 1};
    int type() const override { return Type; }

    float getSpeedPixelsPerFrame();
    QVector2D getVelocityPixelsPerFrame();
    Stop* getCurrentStop();
    bool isWaitingAtStop();

protected:
    void advance(int phase) override;

private slots:
    void busWaitTimerOnTimeout();

private:
    const int BUS_LINE_DIRECTION_FROM_START_TO_END_ = 1;
    const int BUS_LINE_DIRECTION_FROM_END_TO_START_ = -1;

    QString name_;
    std::shared_ptr<BusLine> busLine_;
    float speed_;
    Stop *currentStop_;
    int nextStopIndex_;
    int busLineDirection_;
    QVector2D velocity_;
    QTimer *busWaitTimer_;
    bool isWaitingAtStop_;
    int busStopWaitTimeMilliseconds_;

    void updateGraphics();
    void updateVelocity();
};

#endif // BUS_H
