#include "custombutton.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomButton w;
    w.show();
    QObject::connect(&w,SIGNAL(clicked()),&a,SLOT(quit()));

    return a.exec();
}
