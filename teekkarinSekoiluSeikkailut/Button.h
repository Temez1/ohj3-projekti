#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Button:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Button(QString text="", QGraphicsItem* parent=NULL);
    ~Button();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    void setColor(QColor color);

signals:
    void clicked();

private:
    QGraphicsTextItem *text_;
    QBrush *qbrush_;
};

#endif // BUTTON_H
