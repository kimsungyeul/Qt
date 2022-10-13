#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Paddle : public QGraphicsRectItem
{
public:
    Paddle(QGraphicsItem* parent = 0);

    double getCenterX();

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
};

#endif // PADDLE_H
