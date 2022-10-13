#if 0
// QLCDNumber Widget
#include "widget.h"

#include <QApplication>
#include <QLCDNumber>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget* widget = new QWidget(0);

    QLCDNumber* lcd1 = new QLCDNumber(widget);
    lcd1->setSegmentStyle(QLCDNumber::Flat);
    lcd1->display(2014);
    lcd1->move(10,10);

    QLCDNumber* lcd2 = new QLCDNumber(widget);
    lcd2->setSegmentStyle(QLCDNumber::Flat);
    lcd2->setBinMode();
    lcd2->display(20140000);

    QObject::connect(lcd2, &QLCDNumber::overflow,widget,[](){ qDebug("Overflow"); });
    lcd2->move(10,40);

    QLCDNumber* lcd3 = new QLCDNumber(widget);
    lcd3->setSegmentStyle(QLCDNumber::Flat);
    lcd3->display(2014);
    lcd3->setOctMode();
    lcd3->move(10,70);

    QLCDNumber* lcd4 = new QLCDNumber(widget);
    lcd4->setSegmentStyle(QLCDNumber::Flat);
    lcd4->display(2014);
    lcd4->setDecMode();
    lcd4->move(10,100);

    QLCDNumber* lcd5 = new QLCDNumber(widget);
    lcd5->setSegmentStyle(QLCDNumber::Flat);
    lcd5->display(2014);
    lcd5->setHexMode();
    lcd5->move(10,130);

    widget->resize(120,160);
    widget->show();

    return app.exec();
}
#endif

#if 0
// QProgressBar Widget
#include<QApplication>
#include<QProgressBar>

int main(int argc,char* argv[]){
    QApplication app(argc,argv);

    QProgressBar *pb = new QProgressBar();
    pb->setRange(0,100);
    pb->setValue(20);
    pb->show();

    return app.exec();
}
#endif

#if 0
// QProgressBar moving Widget
#include<QApplication>
#include<QProgressBar>
#include<QTimer>

int main(int argc,char* argv[]){
    QApplication app(argc,argv);

    QProgressBar *pb = new QProgressBar();
    pb->show();

    QTimer timer;
    int n = 0;
    QObject::connect(&timer,&QTimer::timeout,[&](){ pb->setValue(++n%101); });
    timer.start(10);

    return app.exec();

}
#endif

#if 0
// TextBrowser Widget
// Projects -> Run -> Working directory -> right click -> show in explorer
// copy index.html,help.html
#include<QApplication>
#include<QTextBrowser>
#include<QUrl>

int main(int argc,char* argv[]){
    QApplication a(argc,argv);

    QTextBrowser* tb = new QTextBrowser();
    tb->setSource(QUrl("index.html"));
    tb->show();

    return a.exec();
}
#endif

#if 0
// Alt + B => exit, & is accelator
#include<QApplication>
#include<QPushButton>

int main(int argc,char* argv[]){
    QApplication a(argc,argv);

    QPushButton* pushButton = new QPushButton("Push&Button",0);
    QObject::connect(pushButton,SIGNAL(clicked()),&a,SLOT(quit()));
    pushButton->show();

    return a.exec();
}
#endif

#if 0
//QRadioButton,QCheckBox ex
#include<QApplication>
#include<QPushButton>
#include"widget.h"

int main(int argc,char* argv[]){
    QApplication a(argc,argv);
    Widget* w = new Widget(0);
    w->show();

    return a.exec();
}
#endif

#if 0
// QSpinBox ex, SpinBox is correct input possible
#include<QApplication>
#include<QSpinBox>

int main(int argc,char* argv[]){
    QApplication a(argc,argv);

    QSpinBox* spinBox = new QSpinBox();
    spinBox->setRange(0,10);
    spinBox->setSuffix("%");
    spinBox->setWrapping(true);                 // false or comment(//) used in range, overRange impossible.
    spinBox->setSpecialValueText("Percent");
    spinBox->show();

    return a.exec();
}
#endif

#if 0
// QSlider ex, QSlider is correct input impossible
#include<QApplication>
#include<QSlider>
#include<QStyleFactory>
int main(int argc,char* argv[]){
    QApplication a(argc,argv);

    QSlider* slider = new QSlider();
    slider->setOrientation(Qt::Horizontal);
    slider->setTickPosition(QSlider::TicksAbove);
    slider->setStyle(QStyleFactory::create("Fusion"));
    slider->show();

    return a.exec();
}
#endif

#if 0
// QDial ex, QDial is correct input impossible
#include<QApplication>
#include<QDial>

int main(int argc,char* argv[]){
    QApplication a(argc,argv);

    QDial* dial = new QDial();
    dial->setWrapping(true);
    dial->setNotchesVisible(true);
    dial->setNotchTarget(10);
    dial->show();

    return a.exec();
}
#endif

#if 0
// QTimeEdit Widget Example
#include<QApplication>
#include<QTime>
#include<QTimeEdit>

int main(int argc,char* argv[]){
    QApplication a(argc,argv);

    QTimeEdit* timeEdit = new QTimeEdit(0);
    timeEdit->setTime(QTime::currentTime());
    timeEdit->show();

    return a.exec();
}
#endif

#if 0
// QDateEdit Widget Example
#include<QApplication>
#include<QDate>
#include<QDateEdit>

int main(int argc,char* argv[]){
    QApplication a(argc,argv);

    QDateEdit* dateEdit = new QDateEdit(QDate::currentDate(),0);
    dateEdit->setCalendarPopup(true);
    dateEdit->show();

    return a.exec();
}
#endif

#if 0
// QLineEdit Widget Example, number input possible
#include<QApplication>
#include<QLineEdit>

int main(int argc,char* argv[]){
    QApplication a(argc,argv);

    QLineEdit* lineEdit = new QLineEdit();
    lineEdit->setInputMask("099");
    lineEdit->setPlaceholderText("input the number");
    lineEdit->show();

    return a.exec();
}
#endif

#if 1
// QDial + QSlider Example
#include<QApplication>
#include<QPushButton>
#include"widget.h"

int main(int argc,char* argv[]){
    QApplication a(argc,argv);
    Widget* w = new Widget();
    w->show();

    return a.exec();
}
#endif
