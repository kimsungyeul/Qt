#ifndef WIDGET_H
#define WIDGET_H

#if 1
// QWidget 이벤트처리 - moveEvent
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
};
#endif
#endif // WIDGET_H
