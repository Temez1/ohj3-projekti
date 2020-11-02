#include "gameObjects.h"

GameObjects::GameObjects(Player *player,
                         std::vector<std::shared_ptr<BusLineHandler>> buslines,
                         std::unique_ptr<TeekkariHandler> teekkariHandler):
    player(player),
    buslines(buslines),
    teekkariHandler(std::move(teekkariHandler))
{
}
