#include "initScene.h"

#include <unordered_map>

#include "gameObjects/BusLine.h"
#include "gameObjects/handlers/TeekkariHandler.h"
#include "gameObjects/handlers/BusLineHandler.h"
#include "gameObjects/graphical/Bus.h"
#include "gameObjects/graphical/Stop.h"
#include "gameObjects/graphical/Kiosk.h"
#include "gameObjects/graphical/Player.h"
#include "gameObjects/graphical/Food.h"
#include "gameObjects/graphical/lautanen.h"

namespace initScene {

GameObjects* populateMap(QGraphicsScene *scene, unsigned int seed){
    int totalAmountOfStops = 0;
    // When using rand, use srand to change seed in each game
    srand(seed);

    auto map = new QGraphicsSvgItem(":/testitausta");
    scene->addItem(map);

    auto kiosk = new Kiosk(FOOD_PRICE,FOOD_STATE_TIME_IN_SECONDS);

    // BEGIN Best way to crete stops&buses would be one busline at time ?
    std::unordered_map<QString, QPointF> stopLocations_;
    stopLocations_.insert({"keskusta", QPointF(850,330)});
    stopLocations_.insert({"hervanta", QPointF(1500,730)});
    stopLocations_.insert({"lentavanniemi", QPointF(340,120)});
    stopLocations_.insert({"koskipuisto", QPointF(590,330)});
    stopLocations_.insert({"atala", QPointF(1500,160)});
    stopLocations_.insert({"partola", QPointF(200,200)});

    stopLocations_.insert({"Haukiluoma", QPointF(120,350)});
    stopLocations_.insert({"Tesoma", QPointF(120,490)});
    stopLocations_.insert({"Amuri", QPointF(350,490)});
    stopLocations_.insert({"harmala", QPointF(600,800)});
    stopLocations_.insert({"hatanpaa", QPointF(850,800)});
    stopLocations_.insert({"linjaautoasema", QPointF(850,700)});
    stopLocations_.insert({"viinikka", QPointF(1100,700)});
    stopLocations_.insert({"turtola", QPointF(1380,700)});
    stopLocations_.insert({"hakametsa", QPointF(1250,600)});
    stopLocations_.insert({"kissanmaa", QPointF(1350,490)});
    stopLocations_.insert({"kaleva", QPointF(1150,490)});
    stopLocations_.insert({"linnainmaa", QPointF(1500,490)});
    stopLocations_.insert({"lentola", QPointF(1650,490)});


    auto keskusta = new Stop(QString("keskusta"), stopLocations_.at("keskusta"));
    auto hervanta = new Stop(QString("hervanta"), stopLocations_.at("hervanta"));
    auto lentavanniemi = new Stop(QString("lentavanniemi"), stopLocations_.at("lentavanniemi"));
    auto koskipuisto = new Stop(QString("koskipuisto"), stopLocations_.at("koskipuisto"));
    auto atala = new Stop(QString("atala"), stopLocations_.at("atala"));
    auto partola = new Stop(QString("partola"), stopLocations_.at("partola"));
    auto Haukiluoma = new Stop(QString("Haukiluoma"), stopLocations_.at("Haukiluoma"));
    auto Tesoma = new Stop(QString("Tesoma"), stopLocations_.at("Tesoma"));
    auto Amuri = new Stop(QString("Amuri"), stopLocations_.at("Amuri"));
    auto harmala = new Stop(QString("harmala"), stopLocations_.at("harmala"));
    auto hatanpaa = new Stop(QString("hatanpaa"), stopLocations_.at("hatanpaa"));
    auto linjaautoasema = new Stop(QString("linjaautoasema"), stopLocations_.at("linjaautoasema"));
    auto viinikka = new Stop(QString("viinikka"), stopLocations_.at("viinikka"));
    auto turtola = new Stop(QString("turtola"), stopLocations_.at("turtola"));
    auto hakametsa = new Stop(QString("hakametsa"), stopLocations_.at("hakametsa"));
    auto kissanmaa = new Stop(QString("kissanmaa"), stopLocations_.at("kissanmaa"));
    auto kaleva = new Stop(QString("kaleva"), stopLocations_.at("kaleva"));
    auto linnainmaa = new Stop(QString("linnainmaa"), stopLocations_.at("linnainmaa"));
    auto lentola = new Stop(QString("lentola"), stopLocations_.at("lentola"));


    kiosk->setParentItem(lentavanniemi);

    auto stops4 = {keskusta, linjaautoasema, viinikka, turtola, hervanta};
    auto stops3 = {lentavanniemi, Amuri, koskipuisto, keskusta, kaleva, hakametsa, turtola, hervanta};
    auto stops8 = {Haukiluoma, Tesoma, Amuri, koskipuisto, keskusta, kaleva, kissanmaa, linnainmaa, atala};
    auto stops1 = {partola, harmala, hatanpaa, keskusta, kaleva, kissanmaa, linnainmaa, lentola};

    scene->addItem(keskusta);
    scene->addItem(hervanta);
    scene->addItem(lentavanniemi);
    scene->addItem(koskipuisto);
    scene->addItem(atala);
    scene->addItem(partola);
    scene->addItem(Haukiluoma);
    scene->addItem(Tesoma);
    scene->addItem(Amuri);
    scene->addItem(harmala);
    scene->addItem(hatanpaa);
    scene->addItem(linjaautoasema);
    scene->addItem(viinikka);
    scene->addItem(turtola);
    scene->addItem(hakametsa);
    scene->addItem(kissanmaa);
    scene->addItem(kaleva);
    scene->addItem(linnainmaa);
    scene->addItem(lentola);


    auto busLine3 = std::make_shared<BusLine>(BusLine(QString("3"), stops3));
    auto busLine4 = std::make_shared<BusLine>(BusLine(QString("4"), stops4));
    auto busLine1 = std::make_shared<BusLine>(BusLine(QString("1"), stops1));
    auto busLine8 = std::make_shared<BusLine>(BusLine(QString("8"), stops8));
    auto bus3 = new Bus(QString("bus3"), busLine3);
    auto bus4 = new Bus(QString("bus4"), busLine4);
    auto bus8 = new Bus(QString("bus8"), busLine8);
    auto bus1 = new Bus(QString("bus1"), busLine1);

    scene->addItem(bus3);
    scene->addItem(bus4);
    scene->addItem(bus8);
    scene->addItem(bus1);


    auto lautanen1 = new Lautanen("Lautanen1");
    lautanen1->setPos(100,100);
    scene->addItem(lautanen1);

    auto lautanen2 = new Lautanen("Lautanen1");
    lautanen2->setPos(100,300);
    scene->addItem(lautanen2);



    std::vector<std::shared_ptr<BusLine>> buslines = { busLine3 };

    auto busLineHandler = std::make_shared<BusLineHandler>(buslines);

    totalAmountOfStops += stops3.size();
    // END Busline creation

    if ( MAX_AMOUNT_OF_TEEKKARIT_IN_THE_MAP > totalAmountOfStops ){
        throw std::logic_error("Game can't have more teekkarit than stops!");
    }

    if ( INIT_TEEKKARI_AMOUNT > MAX_AMOUNT_OF_TEEKKARIT_IN_THE_MAP){
        throw std::logic_error("Init teekkarit amount can't be more than MAX_AMOUNT_OF_TEEKKARIT_IN_THE_MAP");
    }

    auto teekkariHandler_ = std::make_shared<TeekkariHandler>(scene, busLineHandler,
                                                              INIT_TEEKKARI_AMOUNT,
                                                              TEEKKARI_SPAWN_TIME_IN_SECONDS,
                                                              MAX_AMOUNT_OF_TEEKKARIT_IN_THE_MAP);

    auto player = new Player("Player name", scene, hervanta, PLAYER_STARTING_MONEY, PLAYER_MAX_AMOUNT_OF_FOOD_TO_CARRY);
    scene->addItem(player);

    return new GameObjects(player, busLineHandler, teekkariHandler_);
}

}
