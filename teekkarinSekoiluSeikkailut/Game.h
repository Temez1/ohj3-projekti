#ifndef PELI_H
#define PELI_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>

class Game: public QGraphicsView{
public:
    Game(QWidget *parent=NULL);
    void start();

    QGraphicsScene *scene;
    // BusLines *busLines;

private:
    QGraphicsSvgItem *testMap_;
};

#endif // PELI_H
