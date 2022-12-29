#include <QCoreApplication>
#include <QDebug>
#include <QTest>
#include "dog.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Dog dog;
    QTest::qExec(&dog);

    return a.exec();
}
