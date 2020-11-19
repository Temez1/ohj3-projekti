#include "Game.h"
#include <QDebug>

#include "MainMenu.h"
#include "initScene.h"
#include "gameObjects.h"

Game::Game(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);

    scene = new QGraphicsScene();
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0,0,1920,1030);
    setScene(scene);

    gameLoopTimer_ = new QTimer(this);
    connect(gameLoopTimer_, &QTimer::timeout, scene, &QGraphicsScene::advance);

    mapSeed_ = time(0);

    MainMenu mainmenu(this);
    connect(&mainmenu, &MainMenu::accepted, this, &Game::start);
    connect(&mainmenu, &MainMenu::rejected, this, &Game::quit);
    mainmenu.exec();

    initUI();
    gameObjects_ = initScene::populateMap(scene, mapSeed_);
    initScene::configUI(gameObjects_, progressBar_);

    connect(gameObjects_->player, &Player::playerOutOfMoney, this, &Game::gameOver);
    connect(progressBar_, &ProgressBar::enoughMoneyToPayStudentLoan, this, &Game::gameWon);
}

void Game::initUI()
{
    jumpAndDropBusButton_ = new QPushButton("Jump to bus!", this);
    connect(jumpAndDropBusButton_, &QPushButton::clicked, this, &Game::jumpAndDropBusButtonClicked);

    orderFoodButton_ = new QPushButton("Order food", this);
    connect(orderFoodButton_, &QPushButton::clicked, this, &Game::orderFoodButtonClicked);

    deliverFoodButton_ = new QPushButton("Deliver food", this);
    connect(deliverFoodButton_, &QPushButton::clicked, this, &Game::deliverFoodButtonClicked);

    progressBar_ = new ProgressBar(this);
    progressBar_->setStyleSheet("QProgressBar"
                                "{ border: 2px solid grey; border-radius: 0px; text-align: center; }"
                                "QProgressBar::chunk {background-color: #3add36; width: 1px;}");
    progressBar_->setFormat("Student loan %v/%m€");

    gameOverText_ = new QLabel(this);
}

void Game::start()
{
    gameLoopTimer_->start(16);
}

void Game::quit()
{
    exit(0);
}

void Game::jumpAndDropBusButtonClicked()
{
    if ( gameObjects_->player->jumpToBus() ){
        jumpAndDropBusButton_->setText("Leave the bus!");
        return;
    }

    if ( gameObjects_->player->dropFromBus() ){
        jumpAndDropBusButton_->setText("Jump to bus!");
        return;
    }
}

void Game::orderFoodButtonClicked()
{
    gameObjects_->player->orderFood();
}

void Game::deliverFoodButtonClicked()
{
    gameObjects_->player->deliverFood();
}

void Game::gameOver()
{
    gameOverText_->setText("You lost! :("
                          "Just quit");
}

void Game::gameWon()
{
    gameOverText_->setText("You won! :)"
                          "Just quit");
}

void Game::resizeEvent(QResizeEvent *event)
{
    qDebug() << scene->sceneRect();
    qDebug() << this->width() << this->height();
    this->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    resizeButtons();
    resizeIndicators();

    QGraphicsView::resizeEvent(event);
}

void Game::resizeButtons()
{
    jumpAndDropBusButton_->setGeometry(width() - JUMP_AND_DROP_BUS_BUTTON_WIDTH_PADDING,
                                      height() - JUMP_AND_DROP_BUS_BUTTON_HEIGHT_PADDING,
                                      jumpAndDropBusButton_->width(),
                                      jumpAndDropBusButton_->height());

    orderFoodButton_->setGeometry(width() - ORDER_FOOD_BUTTON_WIDTH_PADDING,
                                           height() - ORDER_FOOD_BUTTON_HEIGHT_PADDING,
                                           orderFoodButton_->width(),
                                           orderFoodButton_->height());

    deliverFoodButton_->setGeometry(width() - DELIVER_FOOD_BUTTON_WIDTH_PADDING,
                                           height() - DELIVER_FOOD_BUTTON_HEIGHT_PADDING,
                                           orderFoodButton_->width(),
                                    orderFoodButton_->height());
}

void Game::resizeIndicators()
{
    progressBar_->setGeometry(width()/2-PROGRESS_BAR_WIDTH/2,
                              PROGRESS_BAR_TOP_PADDING,
                              PROGRESS_BAR_WIDTH,
                              PROGRESS_BAR_HEIGHT);

    gameOverText_->setGeometry(width()/2-gameOverText_->width()/2,
                              height()/2,
                              gameOverText_->width(),
                              gameOverText_->height());
}
