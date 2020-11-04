#include "TeekkariHandler.h"
#include <QDebug>

TeekkariHandler::TeekkariHandler(QGraphicsScene *scene,
                                 std::shared_ptr<BusLineHandler> busLineHandler,
                                 int initTeekkariAmount,
                                 int teekkariSpawnTimeInSeconds,
                                 int maxAmountOfTeekkarit):
    MAX_AMOUNT_OF_TEEKKARIT(maxAmountOfTeekkarit),
    scene_(scene),
    busLineHandler_(busLineHandler),
    teekkariSpawnTimeInMilliseconds_(teekkariSpawnTimeInSeconds * 1000)
{
    for (int i=0; i<initTeekkariAmount; i++) {
        spawnTeekkari();
    }

    teekkariSpawnTimer_ = new QTimer();
    teekkariSpawnTimer_->start(teekkariSpawnTimeInMilliseconds_);
    connect(teekkariSpawnTimer_, &QTimer::timeout, this, &TeekkariHandler::teekkariSpawnTimerOnTimeout);
}

TeekkariHandler::~TeekkariHandler()
{
    delete teekkariSpawnTimer_;
}

int TeekkariHandler::getTeekkaritAmount()
{
    return teekkariStop.size();
}

void TeekkariHandler::teekkariSpawnTimerOnTimeout()
{
    spawnTeekkari();
}

void TeekkariHandler::teekkariReceivedFood(Teekkari *teekkari)
{
    destroyTeekkari(teekkari);
}

void TeekkariHandler::spawnTeekkari()
{
    if ( getTeekkaritAmount() == MAX_AMOUNT_OF_TEEKKARIT ){
        return;
    }

    auto randomStop = findRandomStopWithoutTeekkari();

    auto teekkari = new Teekkari();
    connect(teekkari, &Teekkari::teekkariReceivedFood, this, &TeekkariHandler::teekkariReceivedFood);

    randomStop->addTeekkari(teekkari);
    teekkariStop.insert({teekkari, randomStop});
    teekkari->setParentItem(randomStop);

    qDebug() << "Spawned teekkari at" << randomStop->getName();
    qDebug() << "Amount of teekkarit now" << getTeekkaritAmount();
}

Stop *TeekkariHandler::findRandomStopWithoutTeekkari()
{
    auto randomBusLine = busLineHandler_->getRandomBusLine();
    auto randomStop = randomBusLine->getRandomStop();

    while ( randomStop->hasTeekkari() ) {
        qDebug() << randomStop->getName() << "has teekkari already, trying to find stop without teekkari.";
        randomBusLine = busLineHandler_->getRandomBusLine();
        randomStop = randomBusLine->getRandomStop();
    }

    return randomStop;
}

void TeekkariHandler::destroyTeekkari(Teekkari *teekkari)
{
    auto stop = teekkariStop.at(teekkari);

    stop->removeTeekkari();
    teekkariStop.erase(teekkari);
    scene_->removeItem(teekkari);

    delete teekkari;

    qDebug() << "Amount of teekkarit now" << getTeekkaritAmount();
}
