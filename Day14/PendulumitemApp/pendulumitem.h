#ifndef PENDULUMITEM_H
#define PENDULUMITEM_H

#include <QGraphicsItem>

class PendulumItem : public QGraphicsItem
{
public:
    QRectF boundingRect() const;
    void paint(QPainter* painter,\
               const QStyleOptionGraphicsItem*, QWidget*);
};

#endif // PENDULUMITEM_H
