#ifndef TEEKKARIHANDLER_H
#define TEEKKARIHANDLER_H

#include <unordered_map>

#include <QGraphicsScene>

#include "Teekkari.h"
#include "Stop.h"

class TeekkariHandler
{
public:
    TeekkariHandler(QGraphicsScene *scene, std::vector<Stop *> stops, int initTeekkariAmount);
    const int INIT_TEEKKARI_AMOUNT;

private:
    QGraphicsScene *scene_;
    std::vector<Stop *> stops_;
    QList<Teekkari *> teekkarit_;
};

#endif // TEEKKARIHANDLER_H
