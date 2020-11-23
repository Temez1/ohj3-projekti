#ifndef LAUTANEN_H
#define LAUTANEN_H

#include <QObject>
#include <QGraphicsSvgItem>

class Lautaset: public QGraphicsSvgItem
{

public:
    Lautaset();

public slots:

    void updateLautanenState(int state);

private:

    const int EMPTY = 3;
    const int HOT = 2;
    const int WARM = 1;
    const int COLD = 0;

};

#endif // LAUTANEN_H
