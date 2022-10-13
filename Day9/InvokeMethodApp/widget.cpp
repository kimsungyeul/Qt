#if 0
// invokeMethod Example
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}

double Widget::add(const int a, const float b){
    return a+b;
}
#endif

#if 0
// QSignalMapper Example
#include <QSignalMapper>
#include <QPushButton>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QSignalMapper* mapper = new QSignalMapper(this);
    QPushButton* button[8];
    for(int i=0; i<8; i++){
        button[i] = new QPushButton(QString("Button%1").arg(i+1),this);
        button[i]->setGeometry(30, 40*i, 120, 35);
        connect(button[i], SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(button[i], i);
    }
    connect(mapper, &QSignalMapper::mappedInt, [](int i){ qDebug("%d",i); });
}

Widget::~Widget()
{
}

double Widget::add(const int a, const float b){
    return a+b;
}

#endif

#if 0
// QSignalMapper Example
#include <QSignalMapper>
#include <QPushButton>
#include <QEvent>
#include <QKeyEvent>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}

bool Widget::event(QEvent* e) {
    if (e->type( ) == QEvent::KeyPress) {
        QKeyEvent * ke = (QKeyEvent*)e;
        qDebug( ) << ke->text( );           // Debug창에 키보드입력값출력
        if (ke->key( ) == Qt::Key_Tab) {   // 독자적인 Tab 키 처리
            ke->accept( );
            return true;
        }
    } else if (e->type( ) >= QEvent::User) {
        /* 커스텀(Custom) 이벤트 처리 */
        return true;
    }
    return false;
}

#endif

#if 1
// 사용자정의 Example
#include <QApplication>
#include <QSignalMapper>
#include <QPushButton>
#include <QEvent>
#include <QKeyEvent>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}

bool Widget::event(QEvent* e) {
    if (e->type( ) == QEvent::KeyPress) {
        QKeyEvent * ke = (QKeyEvent*)e;
        qDebug( ) << ke->text( );           // Debug창에 키보드입력값출력
        if (ke->key( ) == Qt::Key_Tab) {   // 독자적인 Tab 키 처리
            ke->accept( );
            return true;
        }
        else if (ke->key( ) == Qt::Key_S) {
            const QEvent::Type CUSTOM_EVENT = static_cast<QEvent::Type>(QEvent::User + 1);
            QApplication::postEvent(this, new QEvent(CUSTOM_EVENT));
        }

    } else if (e->type( ) >= QEvent::User) {
        /* 커스텀(Custom) 이벤트 처리 */
        qDebug() << "User Event : " << e->type( );
        return true;
    }

    return false;
}

#endif
