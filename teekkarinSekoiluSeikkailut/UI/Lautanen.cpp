#include "Lautanen.h"

Lautanen::Lautanen(QWidget *parent) : QSvgWidget(parent)
{
    load(QString(":/emptyLautanen"));
}

void Lautanen::addFood()
{
    load(QString(":/hotFood"));
}

void Lautanen::updateLautanenState(int state)
{
    if (state == WARM)
    {
        load(QString(":/warmFood"));
        return;
    }
    if (state == COLD)
    {
        load(QString(":/coldFood"));
        return;
    }
}
