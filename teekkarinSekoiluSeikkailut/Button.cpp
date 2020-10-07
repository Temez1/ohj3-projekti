#include "Button.h"
#include <QGraphicsTextItem>
#include <QBrush>
#include <QColor>
#include <QDebug>

Button::Button(QString text, QGraphicsItem *parent): QGraphicsRectItem(parent){
    setRect(0,0,200,50);
    // For more colors check https://doc.qt.io/qt-5/qcolor.html
    qbrush_ = new QBrush(Qt::darkCyan, Qt::SolidPattern);
    setBrush(*qbrush_);

    text_ = new QGraphicsTextItem(text,this);
    int xPos = rect().width()/2 - text_->boundingRect().width()/2;
    int yPos = rect().height()/2 - text_->boundingRect().height()/2;
    text_->setPos(xPos,yPos);

    setAcceptHoverEvents(true);
}

Button::~Button()
{
    delete text_;
    delete qbrush_;
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    qbrush_->setColor(Qt::cyan);
    setBrush(*qbrush_);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    qbrush_->setColor(Qt::darkCyan);
    setBrush(*qbrush_);
}

void Button::setColor(QColor color)
{
    qbrush_->setColor(color);
}
