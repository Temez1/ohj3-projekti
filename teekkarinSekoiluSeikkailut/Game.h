#ifndef PELI_H
#define PELI_H

#include <unordered_map>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QTimer>
#include <QString>
#include <QPushButton>

#include "gameObjects/graphical/Player.h"
#include "gameObjects/handlers/TeekkariHandler.h"

#include "gameObjects.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget *parent=NULL);
    QGraphicsScene *scene;

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void start();
    void jumpAndDropBusButtonClicked();
    void orderAndDeliverFoodButtonClicked();

private:
    QTimer *gameLoopTimer_;
    GameObjects *gameObjects_;

    TeekkariHandler *teekkariHandler_;

    // UI Stuff
    QPushButton *jumpAndDropBusButton;
    QPushButton *orderAndDeliverFoodButton;

    const int JUMP_AND_DROP_BUS_BUTTON_WIDTH_PADDING = 120;
    const int JUMP_AND_DROP_BUS_BUTTON_HEIGHT_PADDING = 50;

    const int ORDER_AND_DELIVER_FOOD_BUTTON_WIDTH_PADDING = 240;
    const int ORDER_AND_DELIVER_FOOD_BUTTON_HEIGHT_PADDING = 50;

    void initUI();

    void resizeButtons();
};

#endif // PELI_H
