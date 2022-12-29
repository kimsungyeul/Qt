#ifndef WIDGET_H
#define WIDGET_H

#include <QObject>
#include <QTest>

class Widget : public QObject
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void setAge(int value);
private slots:
    void testFail();
    void testAge();
    void testWidget();

private:
    int age;
};
#endif // WIDGET_H
