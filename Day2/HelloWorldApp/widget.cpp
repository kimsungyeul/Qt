/*
//widget base code
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}
*/

#if 0
#include<QApplication>
#include<QPushButton>

#include "widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent){
    QPushButton *quit = new QPushButton("Quit",this);
    quit->resize(75,35);
    connect(quit,SIGNAL(clicked()),qApp,SLOT(quit()));
}
Widget::~Widget()
{
}
#endif

#if 0
#include<QApplication>
#include<QPushButton>
#include<QLabel>
#include "widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent){
    QPushButton *quit = new QPushButton("Quit",this);
    quit->move(10,10);
    quit->resize(75,35);
    connect(quit,SIGNAL(clicked()),qApp,SLOT(quit()));
    quit->show();
    QLabel *label = new QLabel("<font color=blue>Hello Qt!</font>",this);
    label->setGeometry(10,50,75,35);

    //QLabel label = QLabel("<font color=blue>Hello Qt!</font>",this);
    //label.setGeometry(10,50,75,35);
}
Widget::~Widget()
{
}
#endif

#if 1
#include<QApplication>
#include<QPushButton>
#include<QLabel>
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *quit = new QPushButton("Quit", this);
    quit->move(10, 10);
    quit->resize(125, 35);
#if 1
    connect(quit, SIGNAL(clicked()),
            this, SLOT(slotQuit()));
#else
    connect(quit, &QPushButton::clicked,
            [this](){ slotQuit(); });
#endif
//    quit->show();

    QLabel* label = new QLabel("<font color=blue size=30>"
                               "Hello <i>Qt!</i></font>", this);
    label->setObjectName("label1");
    label->setGeometry(10, 50, 125, 35);
}

void Widget::processClick(){
    emit widgetClicked();
}

Widget::~Widget()
{
}

void Widget::slotQuit(){
    qDebug("slotQuit");
    QLabel* label = findChild<QLabel*>("label1");
    qDebug("%s",qPrintable(label->metaObject()->className()));
    qApp->quit();
}
#endif
