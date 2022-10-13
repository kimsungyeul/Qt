//#include "widget.h"

#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("hello_ko");
    a.installTranslator(&translator);

    QPushButton hello(QObject::tr("Hello"));
    QPushButton world(QObject::tr("world"));
    hello.resize(100,30);
    world.resize(100,30);
    hello.show();
    world.show();

    return a.exec();
}
