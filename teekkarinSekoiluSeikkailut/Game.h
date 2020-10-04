#ifndef PELI_H
#define PELI_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>

#include <BusLines.h>

class Game: public QGraphicsView{
public:
    Game(QWidget *parent=NULL);
    QGraphicsScene *scene;
    BusLines *busLines;
    void start();

private:
    QGraphicsSvgItem *testMap_;
};

#endif // PELI_H
