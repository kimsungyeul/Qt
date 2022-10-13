#if 0
// widget.cpp base code
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}
#endif

#if 0
// QValidator , QRegularExpression , QFormLayout use Example
#include<QFormLayout>
#include<QLabel>
#include<QLineEdit>
#include<QValidator>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QDoubleValidator* doubleValidator = new QDoubleValidator(this);
    //doubleValidator->setRange(10.0,100.0,3);
    doubleValidator->setBottom(10.0);
    doubleValidator->setTop(100.0);
    doubleValidator->setDecimals(3);

    QIntValidator* intValidator = new QIntValidator(this);
    //intValidator->setRange(13,19);
    intValidator->setBottom(13);
    intValidator->setTop(19);

    QRegularExpressionValidator* regExpValidator = new QRegularExpressionValidator(this);
    regExpValidator->setRegularExpression(QRegularExpression("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\." \
                                                             "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."  \
                                                             "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."  \
                                                             "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"));
    //^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$

    QLineEdit* lineEditDouble = new QLineEdit(this);
    lineEditDouble->setValidator(doubleValidator);

    QLineEdit* lineEditint = new QLineEdit(this);
    lineEditint->setValidator(intValidator);

    QLineEdit* lineEditRegExp = new QLineEdit(this);
    lineEditRegExp->setValidator(regExpValidator);

    QFormLayout* formLayout = new QFormLayout(this);
    formLayout->addRow("&Double",lineEditDouble);
    formLayout->addRow("&int",lineEditint);
    formLayout->addRow("&Regular Expression",lineEditRegExp);

    setWindowTitle("Validator");
}

Widget::~Widget()
{
}

#endif

#if 0
// QHBoxLayout class Example
#include<QHBoxLayout>
#include<QPushButton>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton* pushButton1 = new QPushButton();
    pushButton1->setText("Button1");
    QPushButton* pushButton2 = new QPushButton("Button2");
    QPushButton* pushButton3 = new QPushButton("Button3",this);

    QHBoxLayout* hBoxLayout = new QHBoxLayout;
    hBoxLayout->setContentsMargins(50,100,150,200);
    hBoxLayout->addWidget(pushButton1);
    hBoxLayout->addWidget(pushButton2);
    hBoxLayout->addWidget(pushButton3);
    setLayout(hBoxLayout);              // setLayout must using addWidget func added.
}

Widget::~Widget()
{
}
#endif

#if 0
// QVBoxLayout class Example
#include<QVBoxLayout>
#include<QPushButton>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton* pushButton1 = new QPushButton();
    pushButton1->setText("Button1");
    QPushButton* pushButton2 = new QPushButton("Button2");
    QPushButton* pushButton3 = new QPushButton("Button3",this);

    QVBoxLayout* vBoxLayout = new QVBoxLayout(this);        // -> setLayout()
    vBoxLayout->setSpacing(6);
    vBoxLayout->addWidget(pushButton1);
    vBoxLayout->addWidget(pushButton2);
    vBoxLayout->addWidget(pushButton3);
}

Widget::~Widget()
{
}
#endif

#if 0
//QGridLayout class Example
#include<QGridLayout>
#include<QPushButton>

#include "widget.h"
#define NO_OF_ROW 3

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout* gridLayout = new QGridLayout;
    QPushButton* pushButton[NO_OF_ROW*NO_OF_ROW];
    for(int y=0;y<NO_OF_ROW;y++){
        for(int x=0;x<NO_OF_ROW;x++){
            int p = x+y*NO_OF_ROW;
            QString str = QString("Button%1").arg(p+1);
            pushButton[p] = new QPushButton(str,this);
            gridLayout->addWidget(pushButton[p],x,y);
        }
    }
    setLayout(gridLayout);
}

Widget::~Widget()
{
}
#endif

#if 0
// QStackedLayout class Example
// layout is recommend no input parent
// recommend used setLayout

#include<QStackedLayout>
#include<QHBoxLayout>
#include<QDial>
#include<QLabel>
#include<QCalendarWidget>>
#include<QTextEdit>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QDial* dial = new QDial(this);
    dial->setRange(0,2);

    QLabel* label = new QLabel("Stack 1",this);
    QCalendarWidget* calendarWidget = new QCalendarWidget(this);
    QTextEdit* textEdit = new QTextEdit("Stack 3", this);

    QStackedLayout* stackedLayout = new QStackedLayout(); // No (this)  // layout is recommend no input parent
    stackedLayout->addWidget(label);
    stackedLayout->addWidget(calendarWidget);
    stackedLayout->addWidget(textEdit);

    connect(dial,SIGNAL(valueChanged(int)),\
            stackedLayout,SLOT(setCurrentIndex(int)));

    QHBoxLayout* hBoxLayout = new QHBoxLayout();  // No (this)          // layout is recommend no input parent
    hBoxLayout->addWidget(dial);
    hBoxLayout->addLayout(stackedLayout);

    setLayout(hBoxLayout);
}


Widget::~Widget()
{
}
#endif

#if 0
// QFormLayout class Example
#include<QFormLayout>
#include<QLineEdit>
#include<QDateEdit>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLineEdit* ipAddressLineEdit = new QLineEdit(this);
    ipAddressLineEdit->setPlaceholderText("IP Address");
    ipAddressLineEdit->setInputMask("000.000.000.000;_");

    QLineEdit* macAddressLineEdit = new QLineEdit(this);
    macAddressLineEdit->setInputMask("HH:HH:HH:HH:HH:HH;_");

    QDateEdit* dateEdit = new QDateEdit(QDate::currentDate(),this);
    dateEdit->setDisplayFormat("yyyy.MM.dd");

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow("&IP Address",ipAddressLineEdit);
    formLayout->addRow("&Mac Address",macAddressLineEdit);
    formLayout->addRow("&Date",dateEdit);
    setLayout(formLayout);
}

Widget::~Widget()
{
}
#endif

#if 0
// QFrame Widget Example
#include<QFrame>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QFrame* plainLine = new QFrame(this);
    plainLine->setGeometry(QRect(0,0,500,30));
    plainLine->setLineWidth(3);
    plainLine->setFrameStyle(QFrame::HLine | QFrame::Plain);

    QFrame* raisedLine = new QFrame(this);
    raisedLine->setGeometry(QRect(0,30,500,30));
    raisedLine->setLineWidth(3);
    raisedLine->setFrameStyle(QFrame::HLine | QFrame::Raised);

    QFrame* sunkenLine = new QFrame(this);
    sunkenLine->setGeometry(QRect(0,60,500,30));
    sunkenLine->setLineWidth(3);
    sunkenLine->setFrameStyle(QFrame::HLine | QFrame::Sunken);
}

Widget::~Widget()
{
}
#endif

#if 0
// QGroupBox Widget Example
// sizeHint() : write size before check
#include<QGroupBox>
#include<QFormLayout>
#include<QLineEdit>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLineEdit* lineEdit[3];
    for(int i=0;i<3;i++){
        lineEdit[i] = new QLineEdit(this);
    }

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("&IP Address",lineEdit[0]);
    formLayout->addRow("&Mac Address",lineEdit[1]);
    formLayout->addRow("&Date",lineEdit[2]);

    QGroupBox* groupBox = new QGroupBox("Widget Group",this);
    groupBox->move(5,5);
    groupBox->setFlat(false);
    groupBox->setLayout(formLayout);

    resize(groupBox->sizeHint().width()+10, \
           groupBox->sizeHint().height()+10);
}

Widget::~Widget()
{
}
#endif

#if 0
// QTabWidget Widget Example
#include<QTabWidget>
#include<QDial>
#include<QCalendarWidget>
#include<QTextEdit>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QDial* dial = new QDial(this);
    QCalendarWidget* calendarWidget = new QCalendarWidget(this);
    QTextEdit* textEdit = new QTextEdit("Tab 3 edit", this);

    QTabWidget* tabWidget = new QTabWidget(this);
    tabWidget->addTab(dial,"Tab &1");
    tabWidget->addTab(calendarWidget,"Tab &2");
    tabWidget->addTab(textEdit,"Tab &3");

    resize(tabWidget->sizeHint());
}


Widget::~Widget()
{
}
#endif

#if 0
// QSplitter Widget Example
#include<QSplitter>
#include<QLabel>
#include<QDial>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel* label = new QLabel("&IP Address",this);
    QDial* dial = new QDial(this);
    QDial* dial2 = new QDial(this);
    QDial* dial3 = new QDial(this);
    label->setBuddy(dial2);

    QSplitter* splitter = new QSplitter(this);
    splitter->addWidget(label);
    splitter->addWidget(dial);
    splitter->addWidget(dial2);
    splitter->addWidget(dial3);

    resize(splitter->sizeHint());
}


Widget::~Widget()
{
}
#endif
