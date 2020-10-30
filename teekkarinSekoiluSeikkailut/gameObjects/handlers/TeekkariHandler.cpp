#include "TeekkariHandler.h"

#include <QDebug>

TeekkariHandler::TeekkariHandler(QGraphicsScene *scene, std::vector<Stop *> stops, int initTeekkariAmount,
                                 int teekkariSpawnTimeInSeconds):
    scene_(scene),
    stops_(stops),
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
    auto randomStop = *std::next(std::begin(stops_), rand()%(stops_.size()));
    teekkari->setPos(randomStop->pos());
    qDebug() << "Spawned teekkari at" << randomStop->getName();
    scene_->addItem(teekkari);
    teekkarit_.append(teekkari);
}
