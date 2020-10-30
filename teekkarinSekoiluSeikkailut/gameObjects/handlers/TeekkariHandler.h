#ifndef TEEKKARIHANDLER_H
#define TEEKKARIHANDLER_H

#include <QGraphicsScene>
#include <QTimer>

#include "gameObjects/graphical/Teekkari.h"
#include "gameObjects/graphical/Stop.h"

class TeekkariHandler: public QObject
{ Q_OBJECT
public:
    TeekkariHandler(QGraphicsScene *scene, std::vector<Stop *> stops, int initTeekkariAmount,
                    int teekkariSpawnTimeInSeconds);
    ~TeekkariHandler();

private slots:
    void teekkariSpawnTimerOnTimeout();

private:
    QGraphicsScene *scene_;
    std::vector<Stop *> stops_;
    int teekkariSpawnTimeInMilliseconds_;

    QList<Teekkari *> teekkarit_;
    QTimer *teekkariSpawnTimer_;
    void spawnTeekkari();
};

#endif // TEEKKARIHANDLER_H
