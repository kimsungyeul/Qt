#if 0
#include<QLabel>

#include "breakout.h"

#define WIDTH   50
#define HEIGHT  12
#define SCR_WIDTH   300
#define SCR_HEIGHT  400

Breakout::Breakout(QWidget *parent)
    : QWidget(parent)
{
    ball = new QLabel(this);
    ball->setGeometry(SCR_WIDTH*0.8, SCR_HEIGHT*0.875, 10, 10);
    ball->setStyleSheet("QLabel{ background-color:red; border-radius: 5px; }");
    paddle = new QLabel(this);
    paddle->setGeometry(SCR_WIDTH*0.7, SCR_HEIGHT*0.9, WIDTH, HEIGHT);
    paddle->setStyleSheet("QLabel{ background-color:blue; }");

    for(int y=0,i=0; y<5; y++){
        for(int x=0; x<6; x++, i++){
            bricks[i] = new QLabel(this);
            bricks[i]->setStyleSheet("QLabel{ background-color:cyan;"
                                      "border:1px solid black }");
            bricks[i]->setGeometry(x*WIDTH, y*HEIGHT+30, WIDTH, HEIGHT);
        }
    }

    resize(SCR_WIDTH, SCR_HEIGHT);
}

Breakout::~Breakout()
{
    delete ball;
    delete paddle;

    for(int i=0; i<NO_OF_BRICKS; i++){
        delete bricks[i];
    }
}

#endif

#if 1
// 키보드를통한 패들의 이동
#include <QLabel>
#include <QApplication>

#include "breakout.h"

#define WIDTH   50
#define HEIGHT  12
#define SCR_WIDTH   300
#define SCR_HEIGHT  400

Breakout::Breakout(QWidget *parent)
    : QWidget(parent)
{
    ball = new QLabel(this);
    ball->setGeometry(SCR_WIDTH*0.8, SCR_HEIGHT*0.875, 10, 10);
    ball->setStyleSheet("QLabel{ background-color:red; border-radius: 5px; }");
    paddle = new QLabel(this);
    paddle->setGeometry(SCR_WIDTH*0.7, SCR_HEIGHT*0.9, WIDTH, HEIGHT);
    paddle->setStyleSheet("QLabel{ background-color:blue; }");

    for(int y=0,i=0; y<5; y++){
        for(int x=0; x<6; x++, i++){
            bricks[i] = new QLabel(this);
            bricks[i]->setStyleSheet("QLabel{ background-color:cyan;"
                                      "border:1px solid black }");
            bricks[i]->setGeometry(x*WIDTH, y*HEIGHT+30, WIDTH, HEIGHT);
        }
    }

    resize(SCR_WIDTH, SCR_HEIGHT);

    setMouseTracking(true);
}

Breakout::~Breakout()
{
    delete ball;
    delete paddle;

    for(int i=0; i<NO_OF_BRICKS; i++){
        delete bricks[i];
    }
}

void Breakout::keyPressEvent(QKeyEvent* e){
    int x = paddle->pos().x();

    int windowWidth = Breakout::size().width();

    switch(e->key()){
    case Qt::Key_Left:
        x = (x<0)?0:x;
        paddle->move(x-MOVE_SPEED,paddle->y());
        break;
    case Qt::Key_Right:
        //x = (x+WIDTH>SCR_WIDTH)? SCR_WIDTH-WIDTH : x;
        x = (x+WIDTH>windowWidth)? windowWidth-WIDTH : x;
        paddle->move(x+MOVE_SPEED,paddle->y());
        break;
    case Qt::Key_Escape:
        qApp->exit();
        break;
    default:
        QWidget::keyPressEvent(e);
    }
}

void Breakout::mouseMoveEvent(QMouseEvent* e){
    int x = e->pos().x();
    int windowWidth = Breakout::size().width();
    //x = (x<0)?0:(x+WIDTH > width())?width()-WIDTH:x;
    x = (x<0)?0:(x+WIDTH > windowWidth)?windowWidth-WIDTH:x;
    paddle->move(x,paddle->y());
}

#endif
