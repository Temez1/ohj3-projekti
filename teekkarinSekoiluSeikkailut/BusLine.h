#ifndef BUSLINES_H
#define BUSLINES_H

#include <vector>
#include <QString>
#include <QGraphicsSvgItem>

class BusLine
{
public:
    BusLine(QString name, std::vector<QGraphicsSvgItem *> stops);
    QString name;
    int lastStop;

    void addStop(QGraphicsSvgItem *stop);
    // Returns next stop and new direction
    std::pair<int,int> getNextStop(int currentStop, int busDirection);

private:
    const int FIRST_STOP_ = 0;
    const int BUS_DIRECTION_FROM_START_TO_END_ = 1;
    const int BUS_DIRECTION_FROM_END_TO_START_ = -1;

    std::vector<QGraphicsSvgItem *> stops_;

    void checkIsBusDirectionValid(int busDirection);
    void updateLastStop();
};

#endif // BUSLINES_H
