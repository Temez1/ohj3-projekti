#ifndef PELI_H
#define PELI_H

#include <unordered_map>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QTimer>
#include <QString>
#include <QPushButton>
#include "Player.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget *parent=NULL);
    QGraphicsScene *scene;
    Player *player;

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void start();
    void jumpAndDropBusButtonClicked();

private:
    std::unordered_map<QString, QPointF> stopLocations_;

    QGraphicsSvgItem *testMap_;
    QTimer *gameLoopTimer_;

    QPushButton *jumpAndDropBusButton;
    const int JUMP_AND_DROP_BUS_BUTTON_WIDTH_PADDING = 120;
    const int JUMP_AND_DROP_BUS_BUTTON_HEIGHT_PADDING = 50;

    void initScene();
};

#endif // PELI_H
