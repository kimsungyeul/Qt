#include <QCoreApplication>
#include <QVariant>

#include "counter.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Counter a,b;
    //QObject::connect(&a, SIGNAL(valueChanged(int)), &b, SLOT(setValue(int)));
    QObject::connect(&a, SIGNAL(valueChanged(int)), &b, SLOT(setValue(int)));
    a.setValue(30);
    b.setObjectName("kim");
    qDebug("%d", b.value());
    qDebug() << b.property("value");
    qDebug() << b.property("objectName");
    return app.exec();
}
