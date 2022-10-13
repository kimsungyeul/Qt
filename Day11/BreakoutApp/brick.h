#ifndef BRICK_H
#define BRICK_H

#include <QWidget>
#include <QLabel>

//class Brick : public QWidget          // Paddle 클래스와 같이 이미지의 표시를 위해서 부모 클래스로 QLabel 위젯 지정
class Brick : public QLabel
{
    Q_OBJECT
public:
    //explicit Brick(QWidget *parent = nullptr);
    Brick(QWidget *parent = 0);
};

#endif // BRICK_H
