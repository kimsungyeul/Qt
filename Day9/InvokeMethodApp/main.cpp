#if 0
//invokeMethod Method
#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.show();

    double retVal;
    QMetaObject::invokeMethod(&w, "add", Qt::DirectConnection,
                              Q_RETURN_ARG(double, retVal),
                              Q_ARG(int, 42),
                              Q_ARG(float, 9.7f));

    qDebug("%lf", retVal);

    return a.exec();
}
#endif

#if 1
// QEvent class Example
#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.show();

    return a.exec();
}
#endif
