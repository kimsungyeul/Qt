#include <QPainter>

#include "ball.h"

#define RADIUS 10

Ball::Ball(QWidget *parent)
    : QWidget{parent}
{
    resize(RADIUS, RADIUS);
    //setPixmap(QPixmap("ball.png"));
    setStyleSheet("backgroud-color: rgba(0, 0, 0, 0)");     /* 투명한 배경을 설정 */    // a 자리를 0으로 만듬
}

void Ball::paintEvent(QPaintEvent* e){
    Q_UNUSED(e);

    QPainter p(this);
    p.setPen(QColor(Qt::transparent));
    p.setBrush(QColor(Qt::red));
    p.drawEllipse(0, 0, RADIUS, RADIUS);
}
