#include "TeekkariHandler.h"
#include <QDebug>

TeekkariHandler::TeekkariHandler(QGraphicsScene *scene,
                                 std::vector<std::shared_ptr<BusLineHandler>> buslines,
                                 int initTeekkariAmount,
                                 int teekkariSpawnTimeInSeconds,
                                 int maxAmountOfTeekkarit):
    MAX_AMOUNT_OF_TEEKKARIT(maxAmountOfTeekkarit),
    scene_(scene),
    buslines_(buslines),
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

void TeekkariHandler::teekkariReceivedFood(Teekkari *teekkari)
{
    destroyTeekkari(teekkari);
}

void TeekkariHandler::spawnTeekkari()
{
    if ( teekkaritAmount_ == MAX_AMOUNT_OF_TEEKKARIT ){
        return;
    }

    auto teekkari = new Teekkari();
    connect(teekkari, &Teekkari::teekkariReceivedFood, this, &TeekkariHandler::teekkariReceivedFood);

    auto randomBusLine = getRandomBusLine();
    auto randomStop = randomBusLine->getRandomStop();

    while ( randomStop->addTeekkari(teekkari) == false ) {
        qDebug() << randomStop->getName() << "has teekkari already, trying to find stop without teekkari.";
        randomBusLine = getRandomBusLine();
        randomStop = randomBusLine->getRandomStop();
    }

    teekkari->setParentItem(randomStop);
    teekkaritAmount_ += 1;
    qDebug() << "Spawned teekkari at" << randomStop->getName();
    qDebug() << "Amount of teekkarit now" << teekkaritAmount_;
}

void TeekkariHandler::destroyTeekkari(Teekkari *teekkari)
{
    qDebug() << teekkari->parentItem()->type();
    scene_->removeItem(teekkari);
    teekkaritAmount_ -= 1;
    qDebug() << "Amount of teekkarit now" << teekkaritAmount_;
    delete teekkari;
}

std::shared_ptr<BusLineHandler> TeekkariHandler::getRandomBusLine()
{
    return *std::next(std::begin(buslines_), rand()%(buslines_.size()));
}
