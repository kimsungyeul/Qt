#include "dog.h"
#include "qbenchmark.h"
#include "qtestcase.h"

Dog::Dog(QObject *parent)
    : QObject{parent}
{
    qInfo() << "Constructor";
}

void Dog::initTestCase() {
    qInfo() << "initTestCase";
}

void Dog::init() {
    qInfo() << "init";
}

void Dog::cleanup() {
    qInfo() << "cleanup";
}

void Dog::cleanupTestCase() {
    qInfo() << "cleanupTestCase";
}

void Dog::bark() {
    qInfo() << "bark bark bark";
}

void Dog::rollover() {
    qInfo() << "*rolls*";
}

void Dog::simple()
 {
     QString str1 = QLatin1String("This is a test string");
     QString str2 = QLatin1String("This is a test string");
     QCOMPARE(str1.localeAwareCompare(str2), 0);
     // QBENCHMARK {            // 느림
     QBENCHMARK_ONCE {          // 빠름(일반적으로 사용)
         str1.localeAwareCompare(str2);
     }
 }
