#ifndef PELI_H
#define PELI_H

#include <unordered_map>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QTimer>
#include <QString>

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget *parent=NULL);
    QGraphicsScene *scene;

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void start();

private:
    std::unordered_map<QString, QPointF> stopLocations_;

    QGraphicsSvgItem *testMap_;
    QTimer *gameLoopTimer_;

    void initScene();
};

#endif // PELI_H
