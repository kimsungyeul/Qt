#include "widget.h"

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setObjectName("parent");
    QPushButton *quit = new QPushButton("Quit", &w);
    quit->setGeometry(75,30,62,40);
    quit->move(62,40);
    quit->setObjectName("child");
    QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    quit->dumpObjectInfo();
    quit->setGeometry(86,70,200,120);
    w.show();
    w.dumpObjectTree();
    return a.exec();
}
