#ifndef SCENEDATA_H
#define SCENEDATA_H

#include "gameObjects/handlers/BusLineHandler.h"
#include "gameObjects/handlers/TeekkariHandler.h"
#include "gameObjects/graphical/Player.h"
#include "gameObjects/graphical/Stop.h"

class GameObjects
{
public:
    GameObjects(Player *player,
                std::shared_ptr<BusLineHandler> busLineHandler,
                std::shared_ptr<TeekkariHandler> teekkariHandler);

    Player *player;
    std::shared_ptr<BusLineHandler> busLineHandler;
    std::shared_ptr<TeekkariHandler> teekkariHandler;
};

#endif // SCENEDATA_H
