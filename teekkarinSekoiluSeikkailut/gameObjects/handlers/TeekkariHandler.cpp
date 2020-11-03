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
    teekkariSpawnTimeInMilliseconds_(teekkariSpawnTimeInSeconds * 1000),
    teekkaritAmount_(0)
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
    return teekkaritAmount_;
}

void TeekkariHandler::teekkariSpawnTimerOnTimeout()
{
    spawnTeekkari();
}

void TeekkariHandler::teekkariReceivedFood(Stop *teekkariStop)
{
    destroyTeekkari(teekkariStop);
}

void TeekkariHandler::spawnTeekkari()
{
    if ( teekkaritAmount_ == MAX_AMOUNT_OF_TEEKKARIT ){
        return;
    }

    auto randomBusLine = busLineHandler_->getRandomBusLine();
    auto randomStop = randomBusLine->getRandomStop();

    while ( randomStop->hasTeekkari() ) {
        qDebug() << randomStop->getName() << "has teekkari already, trying to find stop without teekkari.";
        randomBusLine = busLineHandler_->getRandomBusLine();
        randomStop = randomBusLine->getRandomStop();
    }

    auto teekkari = new Teekkari(randomStop);
    randomStop->addTeekkari(teekkari);

    teekkari->setParentItem(randomStop);
    teekkaritAmount_ += 1;
    qDebug() << "Spawned teekkari at" << randomStop->getName();
    qDebug() << "Amount of teekkarit now" << teekkaritAmount_;
}

void TeekkariHandler::destroyTeekkari(Stop *teekkariStop)
{

    scene_->removeItem(teekkari);
    teekkaritAmount_ -= 1;
    qDebug() << "Amount of teekkarit now" << teekkaritAmount_;
    delete teekkari;
}
