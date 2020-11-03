#include "gameObjects.h"

GameObjects::GameObjects(Player *player,
                         std::shared_ptr<BusLineHandler> busLineHandler,
                         std::shared_ptr<TeekkariHandler> teekkariHandler):
    player(player),
    busLineHandler(busLineHandler),
    teekkariHandler(teekkariHandler)
{
}
