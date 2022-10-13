#ifndef WIDGET_H
#define WIDGET_H

#if 0
// QWidget 이벤트처리 - moveEvent + QObject타이머 추가
#include <QWidget>
#include <QLabel>

class Widget : public QLabel
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void moveEvent(QMoveEvent*);
    void closeEvent(QCloseEvent*);
    void timerEvent(QTimerEvent* event);
};
#endif

#if 1
// QWidget 이벤트처리 - moveEvent + oneshotTimer추가
#include <QWidget>
#include <QLabel>

class Widget : public QLabel
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void moveEvent(QMoveEvent*);
    void closeEvent(QCloseEvent*);

public slots:
    void displayClock();
};
#endif

#endif // WIDGET_H
