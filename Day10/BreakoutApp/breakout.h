#ifndef BREAKOUT_H
#define BREAKOUT_H

#if 1
// timerEvent 추가, 공의 이동
#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>

class QLabel;

class Breakout : public QWidget
{
    Q_OBJECT

public:
    Breakout(QWidget *parent = nullptr);
    ~Breakout();

protected:
    void keyPressEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent* e);
    void timerEvent(QTimerEvent*);
    void moveObjects();                             // 공의 이동
    void checkCollision();                          // 패들충돌처리
    void autoMode();

protected:
    static const int MOVE_SPEED = 3;                // 패들의 이동속도

private:
    static const int NO_OF_BRICKS = 30;

    QLabel* ball;
    QLabel* paddle;
    QLabel* bricks[NO_OF_BRICKS];
    QLabel* score;

    int timerId;
    int xDir, yDir;
};
#endif

#endif // BREAKOUT_H
