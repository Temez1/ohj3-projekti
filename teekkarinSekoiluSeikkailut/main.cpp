#include <QApplication>
#include <Game.h>
#include <QDebug>

Game *game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();
    qDebug() << "Width:" << game->width();
    qDebug() << "Height:" << game->height();
    return a.exec();
}
