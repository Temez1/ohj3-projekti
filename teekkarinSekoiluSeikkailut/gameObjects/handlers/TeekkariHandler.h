#ifndef TEEKKARIHANDLER_H
#define TEEKKARIHANDLER_H

#include <QGraphicsScene>
#include <QTimer>

#include "gameObjects/graphical/Teekkari.h"
#include "gameObjects/handlers/BusLineHandler.h"

class TeekkariHandler: public QObject
{ Q_OBJECT
public:
    TeekkariHandler(QGraphicsScene *scene, std::vector<std::shared_ptr<BusLineHandler>> buslines, int initTeekkariAmount,
                    int teekkariSpawnTimeInSeconds, int maxAmountOfTeekkarit);
    ~TeekkariHandler();

    const int MAX_AMOUNT_OF_TEEKKARIT;

    int getTeekkaritAmount();

private slots:
    void teekkariSpawnTimerOnTimeout();
    void teekkariReceivedFood(Teekkari *teekkari);

private:
    QGraphicsScene *scene_;
    std::vector<std::shared_ptr<BusLineHandler>> buslines_;

    QTimer *teekkariSpawnTimer_;
    int teekkariSpawnTimeInMilliseconds_;

    int teekkaritAmount_;

    void spawnTeekkari();
    void destroyTeekkari(Teekkari *teekkari);

    std::shared_ptr<BusLineHandler> getRandomBusLine();
};

#endif // TEEKKARIHANDLER_H
