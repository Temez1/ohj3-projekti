#ifndef STOP_H
#define STOP_H

#include <QGraphicsSvgItem>

#include "Kiosk.h"
#include "Teekkari.h"

class Stop: public QGraphicsSvgItem
{
public:
    Stop(QString name, QPointF pos, Kiosk *kiosk=nullptr, QGraphicsItem* parent=NULL);

    enum { Type = UserType + 3};
    int type() const override { return Type; }

    QString getName();
    Kiosk *getKiosk();

    bool addTeekkari(Teekkari *teekkari);
    bool removeTeekkari();
    bool hasTeekkari();

private:
    QString name_;
    Kiosk *kiosk_;
    Teekkari *teekkari_;
};

#endif // STOP_H
