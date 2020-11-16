#ifndef LAUTANEN_H
#define LAUTANEN_H

#include <QObject>
#include <QGraphicsSvgItem>

class Lautanen: public QGraphicsSvgItem
{

public:
    Lautanen(QString name);

public slots:

    void updateLautanenState(int state);

private:
    QString name_;

    const int EMPTY = 3;
    const int HOT = 2;
    const int WARM = 1;
    const int COLD = 0;

};

#endif // LAUTANEN_H
