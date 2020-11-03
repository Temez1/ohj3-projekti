#ifndef TEEKKARI_H
#define TEEKKARI_H

#include <QGraphicsSvgItem>

#include "Stop.h"
#include "Food.h"

class Teekkari : public QGraphicsSvgItem
{ Q_OBJECT
public:
    Teekkari(Stop *stop);

    unsigned int receiveFood(Food food);

private:
    Stop *currentStop_;

signals:
    void teekkariReceivedFood(Stop *currentStop);
};

#endif // TEEKKARI_H
