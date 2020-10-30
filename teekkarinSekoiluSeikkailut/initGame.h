#ifndef INITGAME_H
#define INITGAME_H

#include <QGraphicsScene>

#include "sceneData.h"

namespace initScene {
    SceneData *populateMap(QGraphicsScene *scene);

    const int INIT_TEEKKARI_AMOUNT = 2;
    const QString PLAYER_STARTING_STOP = "hervanta";
}


#endif // INITGAME_H
