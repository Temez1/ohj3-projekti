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

    bool addKiosk(Kiosk *kiosk);
    bool addTeekkari(Teekkari *teekkari);
    bool removeTeekkari();

    QString getName();
    Kiosk *getKiosk();
    Teekkari *getTeekkari();

    bool hasKiosk();
    bool hasTeekkari();

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    const qreal OFFSET_ = 92;
    QString name_;
    Kiosk *kiosk_;
    Teekkari *teekkari_;

    qreal width_;
    qreal height_;
};

#endif // STOP_H
