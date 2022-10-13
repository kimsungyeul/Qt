#if 0
// QWidget 이벤트처리 - moveEvent + QObject타이머 추가
#include<QCloseEvent>
#include<QTimerEvent>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QLabel(parent)
{
    setText("Timer");

    setText(tr("Hello World"));
    resize(100,30);

    int id1 = startTimer(500);           // 50 밀리초 타이머
    int id2 = startTimer(300);         // 1초(1000밀리초) 타이머
}

Widget::~Widget()
{
}

void Widget::moveEvent(QMoveEvent*){
    setText(QString("X : %1, Y : %2").arg(x()).arg(y()));
}

void Widget::closeEvent(QCloseEvent* event){
    event->ignore();            // 이벤트무시
    //event->accept();          // 이벤트허용
}

void Widget::timerEvent(QTimerEvent* event){
    setText(QString::number(event->timerId()));
}
#endif

#if 1
// QWidget 이벤트처리 - moveEvent + oneshotTimer추가
#include<QCloseEvent>
#include<QTimer>
#include<QTime>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QLabel(parent)
{
    QTimer* timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),SLOT(displayClock()));
    timer->start(1000);                 // oneshot Timer
    resize(90,40);
}

Widget::~Widget()
{
}

void Widget::moveEvent(QMoveEvent*){
    //setText(QString("X : %1, Y : %2").arg(x()).arg(y()));
}

void Widget::closeEvent(QCloseEvent* event){
    //event->ignore();            // 이벤트무시
    event->accept();          // 이벤트허용
}

void Widget::displayClock(){
    setText(QTime::currentTime().toString());
}
#endif
