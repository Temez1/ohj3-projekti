#ifndef LAUTANEN_H
#define LAUTANEN_H

#include <QSvgWidget>

#include "gameObjects/graphical/Food.h"

class Lautanen : public QSvgWidget
{
    Q_OBJECT
public:
    explicit Lautanen(QWidget *parent = nullptr);
    void addFood();

public slots:
    void updateLautanenState(int state);
    void playerOrderedFood();
    void playerDeliveredFood();

private:
    const int EMPTY = 3;
    const int HOT = 2;
    const int WARM = 1;
    const int COLD = 0;

};

#endif // LAUTANEN_H
