#include "brick.h"

#define WIDTH 50
#define HEIGHT 12

Brick::Brick(QWidget *parent)
    : QLabel{parent}
{
    resize(WIDTH,HEIGHT);
    setPixmap(QPixmap("brick.png").scaled(WIDTH,HEIGHT));
}
