#ifndef TEEKKARIHANDLER_H
#define TEEKKARIHANDLER_H

#include <unordered_map>

#include <QGraphicsScene>

#include "gameObjects/graphical/Teekkari.h"
#include "gameObjects/graphical/Stop.h"

class TeekkariHandler
{
public:
    TeekkariHandler(QList<Teekkari *> initTeekkarit, std::vector<Stop *> stops);

private:
    QList<Teekkari *> teekkarit_;
    std::vector<Stop *> stops_;
};

#endif // TEEKKARIHANDLER_H
