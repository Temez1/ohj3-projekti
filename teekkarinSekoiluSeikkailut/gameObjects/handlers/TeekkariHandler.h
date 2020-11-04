#ifndef TEEKKARIHANDLER_H
#define TEEKKARIHANDLER_H

#include <unordered_map>

#include <QGraphicsScene>
#include <QTimer>

#include "gameObjects/graphical/Teekkari.h"
#include "gameObjects/handlers/BusLineHandler.h"

class TeekkariHandler: public QObject
{ Q_OBJECT
public:
    TeekkariHandler(QGraphicsScene *scene, std::shared_ptr<BusLineHandler> busLineHandler, int initTeekkariAmount,
                    int teekkariSpawnTimeInSeconds, int maxAmountOfTeekkarit);
    ~TeekkariHandler();

    const int MAX_AMOUNT_OF_TEEKKARIT;

    int getTeekkaritAmount();

private slots:
    void teekkariSpawnTimerOnTimeout();
    void teekkariReceivedFood(Teekkari *teekkari);

private:
    QGraphicsScene *scene_;
    std::shared_ptr<BusLineHandler> busLineHandler_;
    QTimer *teekkariSpawnTimer_;
    int teekkariSpawnTimeInMilliseconds_;

    int teekkaritAmount_;
    std::unordered_map<Teekkari *, Stop*> teekkariStop;

    void spawnTeekkari();
    void destroyTeekkari(Teekkari *teekkari);
    Stop *findRandomStopWithoutTeekkari();
};

#endif // TEEKKARIHANDLER_H
