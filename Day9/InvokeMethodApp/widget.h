#ifndef WIDGET_H
#define WIDGET_H

#if 0
//invokeMethod Example
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    double add(const int a, const float b);

};
#endif

#if 1
//QEvent class Example
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    virtual bool event(QEvent* e);
};
#endif

#endif // WIDGET_H
