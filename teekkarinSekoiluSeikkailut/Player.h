#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>

class Player: public QGraphicsRectItem
{
public:
    Player(QGraphicsScene *scene);

    bool jumpToBus();
    bool isOnTheBus();

private:
    QGraphicsScene *scene_;
    bool isOnTheBus_;
};

#endif // PLAYER_H
