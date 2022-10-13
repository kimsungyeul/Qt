#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QLabel>

//class Ball : public QWidget            // 이미지 표시를 위해서 부모클래스로 QLabel 위젯 지정
class Ball : public QWidget
{
    Q_OBJECT
public:
    //explicit Ball(QWidget *parent = nullptr);
    Ball(QWidget *parent = 0);

private:
    void paintEvent(QPaintEvent* e);
};

#endif // BALL_H
