#include "qlabel.h"
#if 1
//My
#include "calculatorwidget.h"

CalculatorWidget::CalculatorWidget(QWidget *parent)
    : QWidget(parent), isFirst(true)
{
    char str[16][2] = {
        "7", "8", "9", "/",
        "4", "5", "6", "x",
        "1", "2", "3", "-",
        "0", "C", "=", "+"
    };

    label = new QLabel("0", this);
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    label->setGeometry(10, 5, 230, 40);
    label->setObjectName("label1");

    //QPushButton* button[16];
    for(int y = 0; y < WIDTH; ++y) {
        for(int x = 0; x < WIDTH; ++x) {
            button[x+y*WIDTH] = new QPushButton(str[x+y*WIDTH], this);
            button[x+y*WIDTH]->setGeometry(5+60*x, 45+60*y, 60, 60);
        }
    }

    connect(button[0], SIGNAL(clicked()),this, SLOT(numButton()));
    connect(button[1], SIGNAL(clicked()),this, SLOT(numButton()));
    connect(button[2], SIGNAL(clicked()),this, SLOT(numButton()));
    connect(button[4], SIGNAL(clicked()),this, SLOT(numButton()));
    connect(button[5], SIGNAL(clicked()),this, SLOT(numButton()));
    connect(button[6], SIGNAL(clicked()),this, SLOT(numButton()));
    connect(button[8], SIGNAL(clicked()),this, SLOT(numButton()));
    connect(button[9], SIGNAL(clicked()),this, SLOT(numButton()));
    connect(button[10], SIGNAL(clicked()),this, SLOT(numButton()));
    connect(button[12], SIGNAL(clicked()),this, SLOT(numButton()));
    connect(button[13], &QPushButton::clicked,this,[=](){ label->setText("0"); });
    connect(button[14], &QPushButton::clicked,
            [=](){
        double result = 0;
        if(op == "+") {
            result = num1.toDouble() + label->text().toDouble();
        } else if(op == "-") {
            result = num1.toDouble() - label->text().toDouble();
        } else if(op == "x") {
            result = num1.toDouble() * label->text().toDouble();
        } else if(op == "/") {
            result = num1.toDouble() / label->text().toDouble();
        }
        label->setText(QString::number(result));
        isFirst = true;
    });

    connect(button[3], SIGNAL(clicked()),this,SLOT(opButton()));
    connect(button[7], SIGNAL(clicked()),this,SLOT(opButton()));
    connect(button[11], SIGNAL(clicked()),this,SLOT(opButton()));
    connect(button[15], SIGNAL(clicked()),this,SLOT(opButton()));
}

CalculatorWidget::~CalculatorWidget()
{
    delete label;
    for(QPushButton* b : button){
        delete b;
    }
}

//void CalculatorWidget::numButton(){
//    QPushButton* button = dynamic_cast<QPushButton*>(sender());
//    QString bStr = button->text();
//    QLabel* label = findChild<QLabel*>("label1");
//    QString lStr = label->text();
//    label->setText(label->text()=="0"?lStr:lStr+bStr);
//}

void CalculatorWidget::numButton(){
    QPushButton* button = dynamic_cast<QPushButton*>(sender());
    QString bStr;
    if(button != nullptr) bStr = button->text();
    //QLabel* label = findChild<QLabel*>("label1");
    if(label != nullptr) {
        QString lStr = label->text();
        //label->setText(label->text()=="0"?bStr:lStr+bStr);
        label->setText(isFirst?bStr:lStr+bStr);
        isFirst=false;
    }
}

void CalculatorWidget::opButton(){
    QPushButton* button = dynamic_cast<QPushButton*>(sender());
    if(button != nullptr) op = button->text();
    if(label != nullptr) {
        num1 = label->text();
        isFirst=true;
        // label->setText("0");
    }
}

#else
//Pro
#include "calculatorwidget.h"

#include <QLabel>
#include <QPushButton>

#define WITDH 4

CalculatorWidget::CalculatorWidget(QWidget *parent)
    : QWidget(parent), isFirst(true)
{
    char str[16][2] = {
        "7", "8", "9", "/",
        "4", "5", "6", "x",
        "1", "2", "3", "-",
        "0", "C", "=", "+"
    };

    label = new QLabel("0", this);
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    label->setGeometry(10, 5, 230, 40);
    label->setObjectName("label1");
    //    label->setFrameStyle(QFrame::Box);
    //    label->setLineWidth(2);

    for(int y = 0; y < WITDH; ++y) {
        for(int x = 0; x < WITDH; ++x) {
            button.append(new QPushButton(str[x+y*WITDH], this));
            button.at(x+y*WITDH)->setGeometry(5+60*x, 50+60*y, 60, 60);
        }
    }

    connect(button.at(0), SIGNAL(clicked()), SLOT(numButton()));
    connect(button.at(1), SIGNAL(clicked()), SLOT(numButton()));
    connect(button.at(2), SIGNAL(clicked()), SLOT(numButton()));
    connect(button.at(4), SIGNAL(clicked()), SLOT(numButton()));
    connect(button.at(5), SIGNAL(clicked()), SLOT(numButton()));
    connect(button.at(6), SIGNAL(clicked()), SLOT(numButton()));
    connect(button.at(8), SIGNAL(clicked()), SLOT(numButton()));
    connect(button.at(9), SIGNAL(clicked()), SLOT(numButton()));
    connect(button.at(10), SIGNAL(clicked()), SLOT(numButton()));
    connect(button.at(12), SIGNAL(clicked()), SLOT(numButton()));

    connect(button.at(13), &QPushButton::clicked,
            this, [=](){ label->setText("0"); });

    connect(button.at(3), SIGNAL(clicked()), SLOT(opButton()));
    connect(button.at(7), SIGNAL(clicked()), SLOT(opButton()));
    connect(button.at(11), SIGNAL(clicked()), SLOT(opButton()));
    connect(button.at(15), SIGNAL(clicked()), SLOT(opButton()));

    connect(button.at(14), &QPushButton::clicked,
            this, [this](){
        double result = 0;
        if(op == "+") {
            result = num1.toDouble() + label->text().toDouble();
        } else if(op == "-") {
            result = num1.toDouble() - label->text().toDouble();
        } else if(op == "x") {
            result = num1.toDouble() * label->text().toDouble();
        } else if(op == "/") {
            result = num1.toDouble() / label->text().toDouble();
        }
        label->setText(QString::number(result));
        isFirst = true;
    });

}

CalculatorWidget::~CalculatorWidget()
{
    delete label;
    for(QPushButton* b : button)
        delete b;
}

void CalculatorWidget::numButton()
{
    QPushButton* button = dynamic_cast<QPushButton*>(sender());
    QString bStr;
    if(button != nullptr) bStr = button->text();
    QLabel* label = findChild<QLabel*>("label1");
    if(label != nullptr) {
        QString lStr = label->text();
        //label->setText(label->text()=="0"?bStr:lStr+bStr);
        label->setText(isFirst?bStr:lStr+bStr);
        isFirst = false;
    }
}

void CalculatorWidget::opButton()
{
    QPushButton* button = dynamic_cast<QPushButton*>(sender());
    if(button != nullptr) op = button->text();
    if(label != nullptr) {
        num1 = label->text();
        //label->setText("0");
        isFirst = true;
    }
}






#endif
