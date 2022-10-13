#include "widget.h"
#include "filter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    Filter* filter = new Filter(&w);            // filter의 사용
    a.installEventFilter(filter);

    return a.exec();
}
