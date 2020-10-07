#ifndef PELI_H
#define PELI_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QTimer>

#include <BusLines.h>
#include <Button.h>

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget *parent=NULL);
    QGraphicsScene *scene;
    BusLines *busLines;

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void start();

private:
    QGraphicsSvgItem *testMap_;
    Button *testButton_;
    Button *startButton_;
    QTimer *gameLoopTimer_;
};

#endif // PELI_H
