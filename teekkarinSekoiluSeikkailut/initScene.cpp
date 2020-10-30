#include "initScene.h"

#include <unordered_map>

#include "gameObjects/handlers/BusLineHandler.h"
#include "gameObjects/graphical/Bus.h"
#include "gameObjects/graphical/Stop.h"
#include "gameObjects/graphical/Kiosk.h"
#include "gameObjects/graphical/Player.h"

namespace initScene {

SceneData* populateMap(QGraphicsScene *scene){
    auto map = new QGraphicsSvgItem(":/map");
    scene->addItem(map);

    std::unordered_map<QString, QPointF> stopLocations_;
    stopLocations_.insert({"keskusta", QPointF(500,300)});
    stopLocations_.insert({"hervanta", QPointF(900,700)});
    stopLocations_.insert({"lentavanniemi", QPointF(200,300)});

    auto kiosk = new Kiosk();

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

    QList<Teekkari *> teekkarit;

    for (int i=0; i<INIT_TEEKKARI_AMOUNT; i++) {
        auto teekkari = new Teekkari();
        auto randomStop = *std::next(std::begin(stops), rand()%(stops.size()));
        teekkari->setPos(randomStop->pos());
        scene->addItem(teekkari);
        teekkarit.append(teekkari);
    }

    auto player = new Player("Player name", scene);
    player->setPos(stopLocations_.at(PLAYER_STARTING_STOP));
    scene->addItem(player);

    return new SceneData(player, stops, teekkarit);
}

}
