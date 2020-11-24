#ifndef LAUTASET_H
#define LAUTASET_H

#include <QWidget>
#include <QList>

#include "gameObjects/graphical/Player.h"
#include "gameObjects/graphical/Food.h"
#include "UI/Lautanen.h"

class Lautaset: public QWidget
{ Q_OBJECT
public:
    Lautaset(int lautasetPadding, QWidget *parent=nullptr);
    void init(int lautanenAmount, Player *player);

public slots:
    void playerOrderedFood(Food *food);
    void playerDeliveredFood(Food *food);

private:
    const int PADDING_;
    int LAUTANEN_AMOUNT_;
    QList<Lautanen*> lautaset_;
    Player *player_;
};

#endif // LAUTASET_H
