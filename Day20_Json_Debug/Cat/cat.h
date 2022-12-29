#ifndef CAT_H
#define CAT_H

#include <QObject>
#include <QtTest/QtTest>
#include <QTest>

class Cat : public QObject
{
    Q_OBJECT
public:
    explicit Cat(QObject *parent = nullptr);
    void test();

private slots:
    void meow();
    void sleep();
    void speak(QString value);  // did not call due to param!
};

#endif // CAT_H
