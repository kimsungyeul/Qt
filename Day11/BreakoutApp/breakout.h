#ifndef BREAKOUT_H
#define BREAKOUT_H

#if 0
// Sound 추가
// Auto Mode 추가
#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMediaPlayer>

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
    void autoModeMsg();

protected:
    static const int MOVE_SPEED = 3;                // 패들의 이동속도

private:
    static const int NO_OF_BRICKS = 30;
    //static const int NO_OF_BRICKS = 110;

    QLabel* ball;
    QLabel* paddle;
    QLabel* bricks[NO_OF_BRICKS];
    QLabel* score;

    QMediaPlayer* bgPlayer;
    QMediaPlayer* effectPlayer;

    int timerId;
    int xDir, yDir;
    bool automode = false;
    bool autotrig = false;
};
#endif

#if 1
// 새 클래스(Ball,Paddle,Brick) 추가
// QLabel을 없애고 역할들을 클래스화시킴
#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMediaPlayer>

#include "ball.h"
#include "brick.h"
#include "paddle.h"

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
    void paintEvent(QPaintEvent*);

    void timerEvent(QTimerEvent*);
    void moveObjects();                             // 공의 이동
    void checkCollision();                          // 패들충돌처리
    void autoMode();
    void autoModeMsg();

protected:
    static const int MOVE_SPEED = 3;                // 패들의 이동속도

private:
    static const int NO_OF_BRICKS = 30;
    //static const int NO_OF_BRICKS = 110;

    Ball* ball;
    Paddle* paddle;
    Brick* bricks[NO_OF_BRICKS];

    QLabel* score;

    QMediaPlayer* bgPlayer;
    QMediaPlayer* effectPlayer;

    int timerId;
    int xDir, yDir;
    bool automode = false;
    bool autotrig = false;
};
#endif
#endif // BREAKOUT_H
