#ifndef PELI_H
#define PELI_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>

#include <BusLines.h>
#include <Button.h>

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget *parent=NULL);
    QGraphicsScene *scene;
    BusLines *busLines;
    void start();

private:
    QGraphicsSvgItem *testMap_;
    Button *testButton_;
};

#endif // PELI_H
