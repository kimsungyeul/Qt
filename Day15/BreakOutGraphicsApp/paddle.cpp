#include "paddle.h"
#include <QBrush>

Paddle::Paddle(QGraphicsItem* parent)
{
    setRect(0, 0, 85, 18);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);
    setBrush(brush);
}

double Paddle::getCenterX(){
    return x() + rect().width()/2;
}

void Paddle::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    double mouseX = mapToScene(event->pos()).x();               // 마우스에 따라 이동
    setPos(mouseX,y());
}
