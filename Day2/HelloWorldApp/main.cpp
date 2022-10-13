#if 0
// Qt base source
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

#if 0
// Hello world
#include <QApplication>
#include <QLabel>
#include "widget.h"

int main(int argc, char ** argv){
    QApplication app(argc, argv);

    QLabel *hello = new QLabel("<font color = blue> \
                            Hello <i>World! </i></font>",0);
    //Widget w;
    //w.show();
    hello->show();

    return app.exec();
}
#endif

#if 0
// QWidget use method resize()
#include <QApplication>
#include <QLabel>

int main(int argc, char ** argv){
    QApplication app(argc, argv);

    QLabel *hello = new QLabel("<font color = blue> \
                            Hello <i>World! </i></font>",0);
    hello->resize(75,35);
    hello->show();

    return app.exec();
}
#endif

#if 0
// QLabel Widget-> QPushButton
// QPushButton Widget is not rich text ( html source ((ex)size,color...) modify X )
#include <QApplication>
#include <QLabel>
#include <QPushButton>

int main(int argc, char *argv[]){
    QApplication a(argc,argv);
    QPushButton quit("Quit",0);

    quit.resize(75,35);
    quit.show();

    return a.exec();
}
#endif

#if 0
// signal use for quit
#include<QApplication>
#include<QPushButton>

int main(int argc,char* argv[]){
    QApplication a(argc,argv);
    QPushButton quit("Quit",nullptr);

    quit.resize(75,35);
    quit.show();
    QObject::connect(&quit,SIGNAL(clicked()), &a, SLOT(quit()));

    return a.exec();
}
#endif

#if 0
// use Widget
#include<QApplication>
#include<QPushButton>
#include "widget.h"

int main(int argc,char* argv[]){
//    QApplication a(argc,argv);
//    QPushButton quit("Quit",nullptr);

//    quit.resize(75,35);
//    quit.show();
//    QObject::connect(&quit,SIGNAL(clicked()), &a, SLOT(quit()));

//    return a.exec();
    QApplication app(argc,argv);

    QPushButton *button = new QPushButton("Quit",0);
    button->resize(120,35);
    button->move(300,300);
    QObject::connect(button, SIGNAL(clicked()),&app,SLOT(quit()));
    button->show();

    return app.exec();
}
#endif

#if 0
//widget.cpp,widget.h use custom
#include<QApplication>
#include<QPushButton>
#include "widget.h"

int main(int argc,char* argv[]){
//    QApplication a(argc,argv);
//    QPushButton quit("Quit",nullptr);

//    quit.resize(75,35);
//    quit.show();
//    QObject::connect(&quit,SIGNAL(clicked()), &a, SLOT(quit()));

//    return a.exec();
    QApplication app(argc,argv);

    Widget *widget = new Widget(0);
    widget->show();

    //Widget w(nullptr);
    //w.show();

    widget->dumpObjectTree();

    return app.exec();
}
#endif

#if 1
//widget.cpp,widget.h use custom
#include<QApplication>
#include"widget.h"

int main(int argc,char* argv[]){

    QApplication app(argc,argv);

    Widget *widget = new Widget(0);
    QObject::connect(widget,SIGNAL(widgetClicked()),qApp,SLOT(quit()));
    widget->show();

    //widget->dumpObjectTree();

    return app.exec();
}
#endif
















