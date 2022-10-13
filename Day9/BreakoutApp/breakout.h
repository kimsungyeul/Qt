#ifndef BREAKOUT_H
#define BREAKOUT_H

#if 0
#include <QWidget>

class QLabel;

class Breakout : public QWidget
{
    Q_OBJECT

public:
    Breakout(QWidget *parent = nullptr);
    ~Breakout();

private:
    static const int NO_OF_BRICKS = 30;

    QLabel* ball;
    QLabel* paddle;
    QLabel* bricks[NO_OF_BRICKS];
};
#endif

#if 1
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

protected:
    static const int MOVE_SPEED = 3;                // 패들의 이동속도

private:
    static const int NO_OF_BRICKS = 30;

    QLabel* ball;
    QLabel* paddle;
    QLabel* bricks[NO_OF_BRICKS];
};
#endif

#endif // BREAKOUT_H
