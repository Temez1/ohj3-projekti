#ifndef INITGAME_H
#define INITGAME_H

#include <QGraphicsScene>
#include <QProgressBar>

#include "gameObjects.h"

namespace initScene {
    GameObjects *populateMap(QGraphicsScene *scene, unsigned int seed);

    void configUI(GameObjects *gameobjects, QProgressBar *progressBar);

    const int PLAYER_STARTING_MONEY = 50;
    const int PLAYER_MAX_AMOUNT_OF_FOOD_TO_CARRY = 2;

    const int STUDENT_LOAN = 1000;

    const int MAX_AMOUNT_OF_TEEKKARIT_IN_THE_MAP = 3;
    const int INIT_TEEKKARI_AMOUNT = 2;
    const int TEEKKARI_SPAWN_TIME_IN_SECONDS = 20;

    const int FOOD_PRICE = 10;
    const int CHEAPEST_FOOD_PRICE = 10;
    const int FOOD_STATE_TIME_IN_SECONDS = 20;
}


#endif // INITGAME_H
