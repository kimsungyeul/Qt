#ifndef PADDLE_H
#define PADDLE_H

#include <QWidget>
#include <QLabel>

//class Paddle : public QWidget               // Ball 클래스와 같이 이미지의 표시를 위해서 부모클래스로 QLabel 위젯 지정
class Paddle : public QWidget
{
    Q_OBJECT
public:
    //explicit Paddle(QWidget *parent = nullptr);
    Paddle(QWidget *parent = 0);

private:
    void paintEvent(QPaintEvent* e);
};

#endif // PADDLE_H
