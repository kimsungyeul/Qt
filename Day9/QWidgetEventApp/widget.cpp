#if 1
// QWidget 이벤트처리 - moveEvent
#include<QCloseEvent>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QLabel(parent)
{
    setText(tr("Hello World"));
    resize(100,30);
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
#endif
