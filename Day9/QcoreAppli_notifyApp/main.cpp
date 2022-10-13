#include "widget.h"
#include "Application.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Application a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
