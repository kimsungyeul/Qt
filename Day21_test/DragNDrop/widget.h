#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QLabel;
class QLineEdit;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QLabel *label;
    QLineEdit *lineEdit;

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
};
#endif // WIDGET_H
