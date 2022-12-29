#include "widget.h"

Widget::Widget(QWidget *parent)
    : QObject(parent)
{
    age = 0;
}

Widget::~Widget()
{
}

void Widget::setAge(int value) {
    age = value;
}

void Widget::testFail() {
    QFAIL("NO REASON JUST FAIL!!");
}

void Widget::testAge() {
    if(!age) QFAIL("Age is not set!");
}

void Widget::testWidget() {
    int value = 45;

    QVERIFY(age > 0 && age < 100);  //  범위검사

    // 경고출력
    if(age > 40) QWARN("Age is over 40!");
    if(age < 21) QFAIL("Must be an adult!");

    QCOMPARE(age, value);               // 값이 같은지 비교
}
