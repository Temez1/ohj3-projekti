#ifndef TEEKKARI_H
#define TEEKKARI_H

#include <QGraphicsSvgItem>

#include "Food.h"

class Teekkari : public QGraphicsSvgItem
{ Q_OBJECT
public:
    Teekkari();

    unsigned int receiveFood(Food *food);


signals:
    void teekkariReceivedFood(Teekkari *sender);

private:
};

#endif // TEEKKARI_H
