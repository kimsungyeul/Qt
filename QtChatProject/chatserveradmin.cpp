#include "chatserveradmin.h"
#include "ui_chatserveradmin.h"

ChatServerAdmin::ChatServerAdmin(QString cname, quint16 port, QWidget *parent):
    QWidget(parent),
    ui(new Ui::ChatServerAdmin)
{
    ui->setupUi(this);
    ui->clientnamelineEdit->setText(cname);
    ui->portlineEdit->setText(QString::number(port));
    ui->clientnamelineEdit->setReadOnly(true);
    ui->portlineEdit->setReadOnly(true);
    ui->admintextEdit->setReadOnly(true);
}

ChatServerAdmin::~ChatServerAdmin()
{
    delete ui;
}

void ChatServerAdmin::on_sendpushButton_clicked()
{
    //quint16 portNum = ui->portlineEdit->text().toInt();
    QString name = ui->clientnamelineEdit->text();
    QString str = ui->adminlineEdit->text();
    if(str.length()){
        QByteArray bytearray;
        bytearray.clear();
        bytearray = str.toUtf8( );
        /* 화면에 표시 : 앞에 '나'라고 추가 */
        ui->admintextEdit->append("<font color=red>나</font> : " + str);
    }
    //emit sendData(port,str);
    emit sendData(name,str);
}


void ChatServerAdmin::on_quitpushButton_clicked()
{
    qDebug()<<"quit";
}

void ChatServerAdmin::clientChatRecv(QString name, QString str)
{
    if(str.length())
    {
        ui->admintextEdit->append(name + " : " + str);
    }
}
