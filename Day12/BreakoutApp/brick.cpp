#include <QPainter>

#include "brick.h"

#define WIDTH 50
#define HEIGHT 12

Brick::Brick(QWidget *parent)
    : QWidget{parent}
{
    resize(WIDTH,HEIGHT);
    //setPixmap(QPixmap("brick.png").scaled(WIDTH,HEIGHT));
    setStyleSheet("background-color: rgba(0, 0, 0, 0)");        // 직접 드로잉 하기위해 투명하게만듬
}

void Brick::paintEvent(QPaintEvent* e){             // 사각형을 그려야하기때문에 QPainter클래스의 drawRect() 메소드이용
    Q_UNUSED(e);

    QPainter p(this);
    p.setBrush(QColor(Qt::cyan));                   // 펜의색을 지정하지않으면 검은색(기본색) 이 사용됨
    p.drawRect(0, 0, WIDTH, HEIGHT);
}
