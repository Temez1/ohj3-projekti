#ifndef TEEKKARI_H
#define TEEKKARI_H

#include <QGraphicsSvgItem>

#include "Food.h"

class Teekkari : public QGraphicsSvgItem
{ Q_OBJECT
public:
    Teekkari();

    float receiveFood(Food *food);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    const QRectF OFFSET_ = QRectF(-42,-75, 0,0);

signals:
    void teekkariReceivedFood(Teekkari *sender);

private:
};

#endif // TEEKKARI_H
