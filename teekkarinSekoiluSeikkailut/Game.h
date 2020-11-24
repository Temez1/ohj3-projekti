#ifndef PELI_H
#define PELI_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QString>
#include <QPushButton>
#include <QLabel>

#include "GameObjects.h"
#include "UI/ProgressBar.h"
#include "UI/handlers/Lautaset.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget *parent=NULL);
    QGraphicsScene *scene;

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void start();
    void quit();
    void jumpAndDropBusButtonClicked();
    void orderFoodButtonClicked();
    void deliverFoodButtonClicked();

    void gameOver();
    void gameWon();

private:
    QTimer *gameLoopTimer_;
    unsigned int mapSeed_;
    GameObjects *gameObjects_;

    // UI Stuff
    QPushButton *jumpAndDropBusButton_;
    QPushButton *orderFoodButton_;
    QPushButton *deliverFoodButton_;
    ProgressBar *progressBar_;
    QLabel *gameOverText_;
    Lautaset *lautaset_;

    const int JUMP_AND_DROP_BUS_BUTTON_WIDTH_PADDING = 120;
    const int JUMP_AND_DROP_BUS_BUTTON_HEIGHT_PADDING = 50;

    const int ORDER_FOOD_BUTTON_WIDTH_PADDING = 240;
    const int ORDER_FOOD_BUTTON_HEIGHT_PADDING = 50;

    const int DELIVER_FOOD_BUTTON_WIDTH_PADDING = 360;
    const int DELIVER_FOOD_BUTTON_HEIGHT_PADDING = 50;

    const int PROGRESS_BAR_WIDTH = 400;
    const int PROGRESS_BAR_HEIGHT = 30;
    const int PROGRESS_BAR_TOP_PADDING = 20;

    const int LAUTASET_PADDING = 20;

    void initUI();

    void resizeButtons();
    void resizeIndicators();
};

#endif // PELI_H
