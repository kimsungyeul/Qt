#include "breakout.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Breakout w;
    w.show();
    return a.exec();
}
