#ifndef BUSLINES_H
#define BUSLINES_H

#include <vector>
#include <QString>

#include "gameObjects/graphical/Stop.h"

class BusLineHandler
{
public:
    BusLineHandler(QString name, std::vector<Stop *> stops);
    QString name;
    int lastStopIndex;

    void addStop(Stop *stop);
    std::pair<int,int> getNextStopIndexAndNewDirection(int currentStopIndex, int busDirection);
    QPointF getStopPosition(int stopIndex);
    Stop *getStop(int stopIndex);
    Stop *getRandomStop();

private:
    const int FIRST_STOP_INDEX = 0;
    const int BUS_DIRECTION_FROM_START_TO_END_ = 1;
    const int BUS_DIRECTION_FROM_END_TO_START_ = -1;

    std::vector<Stop *> stops_;

    void checkIsBusDirectionValid(int busDirection);
    void checkIsStopIndexValid(int stopIndex);
    void updateLastStop();
};

#endif // BUSLINES_H
