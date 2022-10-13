#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QWidget>
#include <QTimer>

class CustomButton : public QWidget
{
    Q_OBJECT

public:
    CustomButton(QWidget *parent = nullptr);
    ~CustomButton();

private:
    bool m_isEntered;
    bool m_isHighlighted;
    QTimer m_timer;

protected:
    void paintEvent(QPaintEvent*);
    void enterEvent(QEnterEvent*);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent*);

signals:
    void clicked();
};
#endif // CUSTOMBUTTON_H
