#ifndef SCENEDATA_H
#define SCENEDATA_H

#include "gameObjects/handlers/TeekkariHandler.h"
#include "gameObjects/graphical/Player.h"
#include "gameObjects/graphical/Stop.h"

class GameObjects
{
public:
    GameObjects(Player *player, std::vector<Stop *> stops, TeekkariHandler *teekkariHandler);
    Player *player;
    std::vector<Stop *> stops;
    TeekkariHandler *teekkariHandler;
};

#endif // SCENEDATA_H
