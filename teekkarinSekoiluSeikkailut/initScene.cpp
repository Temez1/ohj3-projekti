#include "initScene.h"

#include <unordered_map>

#include "gameObjects/handlers/TeekkariHandler.h"
#include "gameObjects/handlers/BusLineHandler.h"
#include "gameObjects/graphical/Bus.h"
#include "gameObjects/graphical/Stop.h"
#include "gameObjects/graphical/Kiosk.h"
#include "gameObjects/graphical/Player.h"

namespace initScene {

GameObjects* populateMap(QGraphicsScene *scene){
    // When using rand, use srand to change seed in each game
    srand(time(0));

    auto map = new QGraphicsSvgItem(":/map");
    scene->addItem(map);

    std::unordered_map<QString, QPointF> stopLocations_;
    stopLocations_.insert({"keskusta", QPointF(500,300)});
    stopLocations_.insert({"hervanta", QPointF(900,700)});
    stopLocations_.insert({"lentavanniemi", QPointF(200,300)});

    int kioskFoodPrice = 10;
    auto kiosk = new Kiosk(kioskFoodPrice);

    auto keskusta = new Stop(QString("keskusta"), stopLocations_.at("keskusta"));
    auto hervanta = new Stop(QString("hervanta"), stopLocations_.at("hervanta"));
    auto lentavanniemi = new Stop(QString("lentavanniemi"), stopLocations_.at("lentavanniemi"), kiosk);
    kiosk->setParentItem(lentavanniemi);

    auto stops = {keskusta, hervanta, lentavanniemi};

    scene->addItem(keskusta);
    scene->addItem(hervanta);
    scene->addItem(lentavanniemi);

    // This will create a shared pointer that can be used in multiple busses using the same line
    // Shared pointer gets deleted after last bus using the busline gets deleted
    // i.e. If shared pointer is not used anymore
    auto busline = std::make_shared<BusLineHandler>(BusLineHandler(QString("3"), stops));
    auto bus3a = new Bus(QString("3a"), busline);
    auto bus3b = new Bus(QString("3b"), busline, 2, 1);
    auto bus3a_2 = new Bus(QString("3a"), busline, 2, 2, -1);

    scene->addItem(bus3a);
    scene->addItem(bus3b);
    scene->addItem(bus3a_2);

    auto teekkariHandler_ = new TeekkariHandler(scene, stops, INIT_TEEKKARI_AMOUNT, TEEKKARI_SPAWN_TIME_IN_SECONDS);

    auto player = new Player("Player name", scene, hervanta, PLAYER_STARTING_MONEY);
    scene->addItem(player);

    return new GameObjects(player, stops, teekkariHandler_);
}

}
