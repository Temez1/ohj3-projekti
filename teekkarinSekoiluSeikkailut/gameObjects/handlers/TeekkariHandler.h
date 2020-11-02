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
                    int teekkariSpawnTimeInSeconds);
    ~TeekkariHandler();

private slots:
    void teekkariSpawnTimerOnTimeout();

private:
    QGraphicsScene *scene_;
    std::vector<std::shared_ptr<BusLineHandler>> buslines_;
    int teekkariSpawnTimeInMilliseconds_;

    QList<Teekkari *> teekkarit_;
    QTimer *teekkariSpawnTimer_;
    void spawnTeekkari();
};

#endif // TEEKKARIHANDLER_H
