#include "TeekkariHandler.h"

#include <QDebug>

TeekkariHandler::TeekkariHandler(QGraphicsScene *scene,
                                 std::vector<std::shared_ptr<BusLineHandler>> buslines,
                                 int initTeekkariAmount,
                                 int teekkariSpawnTimeInSeconds):
    scene_(scene),
    buslines_(buslines),
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

void TeekkariHandler::teekkariSpawnTimerOnTimeout()
{
    spawnTeekkari();
}

void TeekkariHandler::spawnTeekkari()
{
    auto teekkari = new Teekkari();
    auto randomBusline = *std::next(std::begin(buslines_), rand()%(buslines_.size()));
    auto randomStop = randomBusline->getRandomStop();
    teekkari->setPos(randomStop->pos());
    qDebug() << "Spawned teekkari at" << randomStop->getName();
    scene_->addItem(teekkari);
    teekkarit_.append(teekkari);
}
