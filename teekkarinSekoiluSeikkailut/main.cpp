#include "peliikkuna.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PeliIkkuna w;
    w.show();
    return a.exec();
}
