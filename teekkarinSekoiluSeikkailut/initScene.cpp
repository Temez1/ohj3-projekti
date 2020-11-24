#include "initScene.h"

#include <unordered_map>
#include <QDebug>

#include "gameObjects/BusLine.h"
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

    std::unordered_map<QString, QPointF> stopNamesAndLocations;

    stopNamesAndLocations.insert({"keskusta", QPointF(850,480)});
    stopNamesAndLocations.insert({"hervanta", QPointF(1450,860)});
    stopNamesAndLocations.insert({"lentavanniemi", QPointF(330,260)});
    stopNamesAndLocations.insert({"koskipuisto", QPointF(590,480)});
    stopNamesAndLocations.insert({"atala", QPointF(1500,300)});
    stopNamesAndLocations.insert({"partola", QPointF(300,790)});
    stopNamesAndLocations.insert({"haukiluoma", QPointF(120,350)});
    stopNamesAndLocations.insert({"tesoma", QPointF(120,480)});
    stopNamesAndLocations.insert({"amuri", QPointF(350,480)});
    stopNamesAndLocations.insert({"harmala", QPointF(580,800)});
    stopNamesAndLocations.insert({"hatanpaa", QPointF(840,800)});
    stopNamesAndLocations.insert({"linjaautoasema", QPointF(850,630)});
    stopNamesAndLocations.insert({"viinikka", QPointF(1010,700)});
    stopNamesAndLocations.insert({"turtola", QPointF(1330,700)});
    stopNamesAndLocations.insert({"hakametsa", QPointF(1240,580)});
    stopNamesAndLocations.insert({"kissanmaa", QPointF(1330,480)});
    stopNamesAndLocations.insert({"kaleva", QPointF(1150,480)});
    stopNamesAndLocations.insert({"linnainmaa", QPointF(1510,480)});
    stopNamesAndLocations.insert({"lentola", QPointF(1650,490)});

    std::unordered_map<QString, Stop*> stopsByName;

    for (auto &stopNameAndLocation: stopNamesAndLocations){
        auto stopName = stopNameAndLocation.first;
        auto stop = new Stop(stopName, stopNameAndLocation.second);
        scene->addItem(stop);

        stopsByName.insert({stopName, stop});
    }

    auto kioskLentava = new Kiosk(FOOD_PRICE, FOOD_STATE_TIME_IN_SECONDS, FOOD_PRICE_FACTOR_MODIFIER);
    auto kioskHervanta = new Kiosk(FOOD_PRICE, FOOD_STATE_TIME_IN_SECONDS, FOOD_PRICE_FACTOR_MODIFIER);

    stopsByName.at("lentavanniemi")->addKiosk(kioskLentava);
    stopsByName.at("hervanta")->addKiosk(kioskLentava);

    kioskLentava->setParentItem(stopsByName.at("lentavanniemi"));
    kioskHervanta->setParentItem(stopsByName.at("hervanta"));

    auto stops1 = {stopsByName.at("partola"),
                   stopsByName.at("harmala"),
                   stopsByName.at("hatanpaa"),
                   stopsByName.at("keskusta"),
                   stopsByName.at("kaleva"),
                   stopsByName.at("kissanmaa"),
                   stopsByName.at("linnainmaa"),
                   stopsByName.at("lentola")};

    auto stops3 = {stopsByName.at("lentavanniemi"),
                   stopsByName.at("amuri"),
                   stopsByName.at("koskipuisto"),
                   stopsByName.at("keskusta"),
                   stopsByName.at("kaleva"),
                   stopsByName.at("hakametsa"),
                   stopsByName.at("turtola"),
                   stopsByName.at("hervanta")};

    auto stops4 = {stopsByName.at("keskusta"),
                   stopsByName.at("linjaautoasema"),
                   stopsByName.at("viinikka"),
                   stopsByName.at("turtola"),
                   stopsByName.at("hervanta")};

    auto stops8 = {stopsByName.at("haukiluoma"),
                   stopsByName.at("tesoma"),
                   stopsByName.at("amuri"),
                   stopsByName.at("koskipuisto"),
                   stopsByName.at("keskusta"),
                   stopsByName.at("kaleva"),
                   stopsByName.at("kissanmaa"),
                   stopsByName.at("linnainmaa"),
                   stopsByName.at("atala")};

    auto busLine1 = std::make_shared<BusLine>(BusLine(QString("1"), stops1));
    auto busLine3 = std::make_shared<BusLine>(BusLine(QString("3"), stops3));
    auto busLine4 = std::make_shared<BusLine>(BusLine(QString("4"), stops4));
    auto busLine8 = std::make_shared<BusLine>(BusLine(QString("8"), stops8));

    createBusesInBusLine(scene, busLine1, stops1, BUS_LINE_1_BUS_AMOUNT);
    createBusesInBusLine(scene, busLine3, stops3, BUS_LINE_3_BUS_AMOUNT);
    createBusesInBusLine(scene, busLine4, stops4, BUS_LINE_4_BUS_AMOUNT);
    createBusesInBusLine(scene, busLine8, stops8, BUS_LINE_8_BUS_AMOUNT);

    std::vector<std::shared_ptr<BusLine>> buslines = { busLine1, busLine3, busLine4, busLine8 };

    auto busLineHandler = std::make_shared<BusLineHandler>(buslines);

    if ( MAX_AMOUNT_OF_TEEKKARIT_IN_THE_MAP > stopNamesAndLocations.size() ){
        throw std::logic_error("Game can't have more teekkarit than stops!");
    }

    if ( INIT_TEEKKARI_AMOUNT > MAX_AMOUNT_OF_TEEKKARIT_IN_THE_MAP){
        throw std::logic_error("Init teekkarit amount can't be more than MAX_AMOUNT_OF_TEEKKARIT_IN_THE_MAP");
    }

    auto teekkariHandler = std::make_shared<TeekkariHandler>(scene, busLineHandler,
                                                              INIT_TEEKKARI_AMOUNT,
                                                              TEEKKARI_SPAWN_TIME_IN_SECONDS,
                                                              MAX_AMOUNT_OF_TEEKKARIT_IN_THE_MAP);

    auto player = new Player("Player name", scene, stopsByName.at("hervanta"), PLAYER_STARTING_MONEY,
                             PLAYER_MAX_AMOUNT_OF_FOOD_TO_CARRY, CHEAPEST_FOOD_PRICE);
    scene->addItem(player);

    return new GameObjects(player, busLineHandler, teekkariHandler);
}

void configUI(GameObjects *gameobjects, ProgressBar *progressBar, Lautaset *lautaset)
{
    progressBar->setMaximum(STUDENT_LOAN);
    progressBar->setValue(PLAYER_STARTING_MONEY);
    QObject::connect(gameobjects->player->getWallet(), &Wallet::balanceChanged, progressBar,
                     &ProgressBar::walletBalanceChanged);

    lautaset->init(PLAYER_MAX_AMOUNT_OF_FOOD_TO_CARRY, gameobjects->player);
}
    namespace {
        void createBusesInBusLine(QGraphicsScene *scene, std::shared_ptr<BusLine> busline, std::vector<Stop*> stops, int busAmount)
        {
            for (int i=0; i< busAmount; i++) {
                auto speed = (rand()%10+1)*0.1 + BUS_DEFAULT_SPEED;

                auto startingStop = (i * (stops.size() + 1) / busAmount);

                if (busAmount == 2 and i == 1){
                    startingStop = stops.size() - 1;
                }

                auto startingDirection = (rand()%1 == 0) ? -1 : 1;
                auto busWaitTimeInMilliseconds = rand()%2000 + 1000;

                auto bus = new Bus(QString("bus"+busline->name), busline, speed, startingStop, startingDirection, busWaitTimeInMilliseconds);
                scene->addItem(bus);
            }
        }
    }
}
