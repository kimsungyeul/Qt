#include "block.h"
#include <QBrush>

Block::Block(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(0, 0, 55, 28);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
    setBrush(brush);
}
