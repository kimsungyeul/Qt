#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_lineEdit_textChanged(const QString &arg1)
{
    ui->spinBox->blockSignals(true);
    ui->dial->setValue(arg1.toInt());
    ui->spinBox->blockSignals(false);

//    // 혹은 아래처럼 disconnect를 해주고 다시 connect로 연결해줌
//    ui->spinBox->disconnect(ui->lineEdit);
//    ui->dial->setValue(arg1.toInt());
//    connect(ui->spinBox,SIGNAL(textChanged(QString)),ui->lineEdit,SLOT(setText(QString)));
}

