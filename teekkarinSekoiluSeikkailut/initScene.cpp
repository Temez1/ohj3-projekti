#include "initScene.h"

#include <unordered_map>

#include "gameObjects/handlers/TeekkariHandler.h"
#include "gameObjects/handlers/BusLineHandler.h"
#include "gameObjects/graphical/Bus.h"
#include "gameObjects/graphical/Stop.h"
#include "gameObjects/graphical/Kiosk.h"
#include "gameObjects/graphical/Player.h"
#include "gameObjects/graphical/Food.h"

namespace initScene {

GameObjects* populateMap(QGraphicsScene *scene, unsigned int seed){
    // When using rand, use srand to change seed in each game
    srand(seed);

    auto map = new QGraphicsSvgItem(":/map");
    scene->addItem(map);

    auto food = Food(FOOD_PRICE);
    auto kiosk = new Kiosk(food);

    // BEGIN Best way to crete stops&buses would be one busline at time ?
    std::unordered_map<QString, QPointF> stopLocations_;
    stopLocations_.insert({"keskusta", QPointF(500,300)});
    stopLocations_.insert({"hervanta", QPointF(900,700)});
    stopLocations_.insert({"lentavanniemi", QPointF(200,300)});

    auto keskusta = new Stop(QString("keskusta"), stopLocations_.at("keskusta"));
    auto hervanta = new Stop(QString("hervanta"), stopLocations_.at("hervanta"));
    auto lentavanniemi = new Stop(QString("lentavanniemi"), stopLocations_.at("lentavanniemi"), kiosk);
    kiosk->setParentItem(lentavanniemi);

    auto stops = {keskusta, hervanta, lentavanniemi};

    scene->addItem(keskusta);
    scene->addItem(hervanta);
    scene->addItem(lentavanniemi);

    auto busLine3 = std::make_shared<BusLineHandler>(BusLineHandler(QString("3"), stops));
    auto bus3a = new Bus(QString("3a"), busLine3);
    auto bus3b = new Bus(QString("3b"), busLine3, 2, 1);
    auto bus3a_2 = new Bus(QString("3a"), busLine3, 2, 2, -1);

    scene->addItem(bus3a);
    scene->addItem(bus3b);
    scene->addItem(bus3a_2);

    std::vector<std::shared_ptr<BusLineHandler>> buslines = { busLine3 };
    // END Busline creation

    auto teekkariHandler_ = std::make_unique<TeekkariHandler>(scene, buslines, INIT_TEEKKARI_AMOUNT, TEEKKARI_SPAWN_TIME_IN_SECONDS);

    auto player = new Player("Player name", scene, hervanta, PLAYER_STARTING_MONEY, PLAYER_MAX_AMOUNT_OF_FOOD_TO_CARRY);
    scene->addItem(player);

    return new GameObjects(player, buslines, std::move(teekkariHandler_));
}

}
