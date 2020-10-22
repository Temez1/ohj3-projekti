#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>

class Player: public QGraphicsRectItem
{
public:
    Player(QString name, QGraphicsScene *scene);

    enum { Type = UserType + 2};
    int type() const override { return Type; }

    bool jumpToBus();
    bool isOnTheBus();

private:
    QString name_;
    QGraphicsScene *scene_;
    bool isOnTheBus_;
};

#endif // PLAYER_H
