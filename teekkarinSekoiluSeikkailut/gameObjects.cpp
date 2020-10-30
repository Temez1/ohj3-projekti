#include "gameObjects.h"

GameObjects::GameObjects(Player *player, std::vector<Stop *> stops, TeekkariHandler *teekkariHandler):
    player(player),
    stops(stops),
    teekkariHandler(teekkariHandler)
{
}
