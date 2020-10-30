#ifndef SCENEDATA_H
#define SCENEDATA_H

#include "gameObjects/graphical/Player.h"
#include "gameObjects/graphical/Stop.h"
#include "gameObjects/graphical/Teekkari.h"

class SceneData
{
public:
    SceneData(Player *player, std::vector<Stop *> stops, QList<Teekkari *>teekkarit);
    Player *player;
    std::vector<Stop *> stops;
    QList<Teekkari *>teekkarit;
};

#endif // SCENEDATA_H
