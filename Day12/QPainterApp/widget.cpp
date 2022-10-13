#if 0
// QPainter 클래스 - 점
#include <QPainter>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent*) {
    QPainter* painter = new QPainter(this);
    painter->setPen(QPen(Qt::blue, 4, Qt::DashLine));
    painter->drawPoint(100, 100);
    delete painter;
}
#endif

#if 0
// QPainter 클래스 - 선
#include <QPainter>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent*) {
    QPainter* painter = new QPainter(this);
    painter->setPen(QPen(Qt::blue, 5, Qt::DashLine));
    painter->drawLine(20, 20, 160, 160);
    delete painter;
}
#endif

#if 0
// QPainter 클래스 - 사각형
#include <QPainter>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent*) {
    QPainter* painter = new QPainter(this);
    painter->setPen(QPen(Qt::blue, 5, Qt::SolidLine));
    painter->drawRect(20, 20, 160, 160);
    delete painter;
}
#endif

#if 0
// QPainter 클래스 - 둥근 사각형
#include <QPainter>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent*) {
    QPainter* painter = new QPainter(this);
    painter->setPen(QPen(Qt::blue, 5, Qt::SolidLine));
    painter->drawRoundedRect(20, 20, 160, 160, 50, 80);
    delete painter;
}
#endif

#if 0
// QPainter 클래스 - 원
#include <QPainter>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent*) {
    QPainter* painter = new QPainter(this);
    painter->setPen(QPen(Qt::blue, 5, Qt::SolidLine));
    //painter->drawEllipse(20, 20, 140, 170);               // 20,20 시작점으로 140, 170 크기의 원그리기
    //painter->drawEllipse(20, 20, 170, 170);               // 20,20 시작점으로 170,170 크기의 원 그리기
    painter->drawEllipse(QPoint(100, 100), 80, 80);         // 100,100 중심으로부터 80,80의 원그리기
    delete painter;
}
#endif

#if 0
// QPainter 클래스 - 원의 외각선1
// 호(Arc)
// 각도 : 1/16 단위로 표시 ( 한 원: 16 X 360 = 5760 의 값으로 표현 )
#include <QPainter>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent*) {
    QPainter* painter = new QPainter(this);
    painter->setPen(QPen(Qt::blue, 5, Qt::DotLine));
    painter->drawArc(20, 20, 160, 160, 30*16, 150*16);
    delete painter;
}
#endif

#if 0
// QPainter 클래스 - 원의 외각선2
// 현(Chord)
#include <QPainter>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent*) {
    QPainter* painter = new QPainter(this);
    painter->setPen(QPen(Qt::blue, 5, Qt::SolidLine));
    painter->drawChord(20, 20, 160, 160, 30*16, 150*16);
    delete painter;
}
#endif

#if 0
// QPainter 클래스 - 원의 외각선2
// 파이(Pie)
#include <QPainter>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent*) {
    QPainter* painter = new QPainter(this);
    painter->setPen(QPen(Qt::blue, 5, Qt::SolidLine));
    painter->drawPie(20, 20, 160, 160, 50*16, 130*16);
    delete painter;
}
#endif

#if 0
// 다각형 그리기(QPainter)1
#include <QPainter>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent*) {
    QPainter* painter = new QPainter(this);
    painter->setPen(QPen(Qt::blue, 5, Qt::SolidLine));
    static const QPoint points[6] = {
        QPoint(20, 20),
        QPoint(20, 90),
        QPoint(90, 80),
        QPoint(80, 160),
        QPoint(160, 80),
        QPoint(80, 20)
    };
    //painter->drawPolygon(points,6);             // 폐곡선
    //painter->drawPolyline(points,6);      // 개곡선
    painter->drawLines(points,6);
    //painter->drawPoints(points,6);
    delete painter;
}
#endif

#if 0
// 다각형 그리기(QPainter)2
#include <QPainter>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent*) {
    QPainter* painter = new QPainter(this);
    painter->setPen(QPen(Qt::blue, 5, Qt::SolidLine));
    QVector<QPoint> pointsVector;
    pointsVector << QPoint(20, 20)\
                 << QPoint(20, 90)\
                 << QPoint(90, 80)\
                 << QPoint(80, 160)\
                 << QPoint(160, 80)\
                 << QPoint(80, 20);
    //painter->drawPolygon(pointsVector);         // 폐곡선
    //painter->drawPolyline(pointsVector);        // 개곡선
    painter->drawLines(pointsVector);
    //painter->drawPoints(pointsVector);
    delete painter;
}
#endif

#if 0
// QPainter 클래스 - 문자(Text)
#include <QPainter>
#include <QFontDialog>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
    //QFont seriFont("Times", 10, QFont::Bold);
    font = QFontDialog::getFont(&ok, this);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent*){
    QPainter* painter = new QPainter(this);
    painter->setPen(QPen(Qt::blue, 5, Qt::SolidLine));
    painter->setFont(font);
    painter->drawText(20, 20, "Hello Qt!");

    delete painter;
}
#endif

#if 0
// QGradient 클래스선형 그래디언트
#include <QPainter>
#include <QFontDialog>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent*){
//    // 선형 그래디언트
//    QLinearGradient gradient(0, 0, 100, 180);
//    gradient.setColorAt(0.0, Qt::red);
//    gradient.setColorAt(1.0, Qt::green);

    // 원뿔형 그래디언트
    QRadialGradient gradient(102, 102, 85);
    //gradient.RepeatSpread;
    gradient.setColorAt(0.0, Qt::red);
    gradient.setColorAt(0.5, Qt::blue);
    gradient.setColorAt(1.0, Qt::green);

    QPainter painter;
    painter.begin(this);
    painter.setBrush(gradient);
    painter.drawRect(20, 20, 160, 160);
    painter.end();
}
#endif

#if 0
// QPainterPath 클래스
#include <QPainter>
#include <QPainterPath>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(200,200);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent*){
    QPainterPath path;
    path.addRect(20, 20, 60, 60);

    path.moveTo(0, 0);
    path.cubicTo(99, 0,  50, 50,  99, 99);
    path.cubicTo(0, 99,  50, 50,  0, 0);

    QPainter painter(this);
    painter.fillRect(0, 0, 100, 100, Qt::white);
    painter.setPen(QPen(QColor(79, 106, 25), 1, Qt::SolidLine,
                        Qt::FlatCap, Qt::MiterJoin));
    painter.setBrush(QColor(122, 163, 39));

    painter.drawPath(path);
}
#endif
