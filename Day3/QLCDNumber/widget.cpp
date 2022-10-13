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
// QRadioButton ex
#include<QRadioButton>
#include<QButtonGroup>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(280,110);
    buttonGroup = new QButtonGroup(this);
    for(int i=0;i<8;i++){
        if(i<4){
            QString str = QString("RadioButton%1").arg(i+1);
            radioButton[i] = new QRadioButton(str,this);
            radioButton[i]->move(10,10+20*i);
            buttonGroup->addButton(radioButton[i]);
        }
        else{
            QString str = QString("RadioButton%1").arg(i+1);
            radioButton[i] = new QRadioButton(str,this);
            radioButton[i]->move(150,10+20*(i-4));
            buttonGroup->addButton(radioButton[i]);
        }
    }
}

Widget::~Widget()
{
}
#endif

#if 0
// QCheckBox ex
#include<QCheckBox>
#include<QButtonGroup>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(140,120);
    label = new QLabel("0", this);
    label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label->setGeometry(10, 5, 140, 30);

    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);               // false -> multi select possible
    connect(buttonGroup,SIGNAL(idClicked(int)),SLOT(selectButton(int)));
    for(int i=0;i<4;i++){
        QString str = QString("QCheckBox%1").arg(i+1);
        checkBox[i] = new QCheckBox(str,this);
        checkBox[i]->move(10,35+20*i);
        buttonGroup->addButton(checkBox[i],i);
    }
}

Widget::~Widget()
{
}

void Widget::selectButton(int id){
    QButtonGroup* bg = dynamic_cast<QButtonGroup*>(sender());
    //QCheckBox* button = (QCheckBox*)buttonGroup->button(id);
    QCheckBox* button = dynamic_cast<QCheckBox*>(bg->button(id));
    if(label != nullptr) {
        QString bStr = button->text();
        //label->setText(QString::number(id+1));
        label->setText(bStr);
    }
    qDebug("CheckBox%d is selected(%s)",id+1,(button->isChecked())?"On":"Off");
}
#endif

#if 1
// QDial + QSlider Example
#include "widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    slider = new QSlider(this);
    slider->setGeometry(10,5,200,30);
    slider->setOrientation(Qt::Horizontal);
    slider->setTickPosition(QSlider::TicksAbove);
    slider->setStyle(QStyleFactory::create("Fusion"));

    dial = new QDial(this);
    dial->setGeometry(10, 40,200,200);

    connect(slider,SIGNAL(valueChanged(int)), dial, SLOT(setValue(int)));
    connect(dial,SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
}

Widget::~Widget()
{
}
#endif
