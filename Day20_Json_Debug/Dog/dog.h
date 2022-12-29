#ifndef DOG_H
#define DOG_H

#include <QObject>
#include <QDebug>

class Dog : public QObject
{
    Q_OBJECT
public:
    explicit Dog(QObject *parent = nullptr);

private slots:
    void initTestCase();            // 첫 테스트 함수 전 호출
    void init();                    // 각각의 테스트 함수 전 호출
    void cleanup();                 // 각각의 테스트 함수 후 호출
    void cleanupTestCase();         // 마지막 테스트 함수 후 호출

    void bark();                    // 테스트를 위한 슬롯
    void rollover();

    void simple();
};

#endif // DOG_H
