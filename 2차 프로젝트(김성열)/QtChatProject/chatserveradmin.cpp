#include "chatserveradmin.h"
#include "ui_chatserveradmin.h"
#include <QApplication>

ChatServerAdmin::ChatServerAdmin(QString cname, quint16 port, QWidget *parent):
    QWidget(parent),
    ui(new Ui::ChatServerAdmin)
{
    ui->setupUi(this);
    ui->clientnamelineEdit->setText(cname);                             // clientnamelineEdit를 cname으로 설정
    ui->portlineEdit->setText(QString::number(port));                   // portlineEdit을 port로 설정
    ui->clientnamelineEdit->setReadOnly(true);                          // clientnamelineEdit readonly로 설정
    ui->portlineEdit->setReadOnly(true);                                // portlineEdit readonly로 설정
    ui->admintextEdit->setReadOnly(true);                               // admintextEdit readonly로 설정
    connect(ui->quitpushButton, SIGNAL(clicked()), SLOT(close()));      // quit버튼클릭스 windwo close
}

ChatServerAdmin::~ChatServerAdmin()
{
    delete ui;
}

void ChatServerAdmin::on_sendpushButton_clicked()
{
    QString name = ui->clientnamelineEdit->text();                      // clientnamelineEdit의 text를 name에저장
    QString str = ui->adminlineEdit->text();                            // adminlineEdit text를 str에저장
    if(str.length()){
        QByteArray bytearray;
        bytearray = str.toUtf8( );
        ui->admintextEdit->append("<font color=red>나</font> : " + str); // 화면에 표시 : 앞에 '나'라고 추가
    }
    emit sendData(name,str);                                            // 이름, 메세지내용을전달하는 시그널
}

void ChatServerAdmin::clientChatRecv(QString name, QString str)         // client로부터 메세지를 받으면실행되는 슬롯
{
    if(str.length())
    {
        ui->admintextEdit->append(name + " : " + str);                  // 채팅을 받으면 admintextedit에 항목추가
    }
}
