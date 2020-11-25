#ifndef INITGAME_H
#define INITGAME_H

#include <QGraphicsScene>

#include "GameObjects.h"
#include "UI/ProgressBar.h"
#include "UI/handlers/Lautaset.h"

namespace initScene {
    GameObjects *populateMap(QGraphicsScene *scene, unsigned int seed);

    void configUI(GameObjects *gameobjects, ProgressBar *progressBar, Lautaset *lautaset);

    const int PLAYER_STARTING_MONEY = 50;
    const int PLAYER_MAX_AMOUNT_OF_FOOD_TO_CARRY = 3;

    const int STUDENT_LOAN = 1000;

    const int MAX_AMOUNT_OF_TEEKKARIT_IN_THE_MAP = 12;
    const int INIT_TEEKKARI_AMOUNT = 2;
    const int TEEKKARI_SPAWN_TIME_IN_SECONDS = 20;

    const int FOOD_PRICE = 10;
    const int CHEAPEST_FOOD_PRICE = 10;
    const int FOOD_STATE_TIME_IN_SECONDS = 20;
    const double FOOD_PRICE_FACTOR_MODIFIER = 2;

    const int BUS_DEFAULT_SPEED = 3;

    const int BUS_LINE_1_BUS_AMOUNT = 3;
    const int BUS_LINE_3_BUS_AMOUNT = 3;
    const int BUS_LINE_4_BUS_AMOUNT = 2;
    const int BUS_LINE_8_BUS_AMOUNT = 3;

    namespace {
        void createBusesInBusLine(QGraphicsScene *scene, std::shared_ptr<BusLine> busline,
                                  std::vector<Stop*> stops, int busAmount);
    }
}


#endif // INITGAME_H
