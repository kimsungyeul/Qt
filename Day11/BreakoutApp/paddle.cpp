#include "paddle.h"

#define WIDTH 50
#define HEIGHT 12

Paddle::Paddle(QWidget *parent)
    : QLabel{parent}
{
    resize(WIDTH,HEIGHT);
    setPixmap(QPixmap("paddle.png").scaled(WIDTH,HEIGHT));
}
