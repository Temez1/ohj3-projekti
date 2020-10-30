#include "sceneData.h"

SceneData::SceneData(Player *player, std::vector<Stop *> stops, QList<Teekkari *>teekkarit):
    player(player),
    stops(stops),
    teekkarit(teekkarit)
{
}
