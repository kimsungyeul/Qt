#ifndef CHATSERVERADMIN_H
#define CHATSERVERADMIN_H

#include <QWidget>
#include "chatserver.h"

#define BLOCK_SIZE  1024

namespace Ui {
class ChatServerAdmin;
}

class ChatServerAdmin : public QWidget
{
    Q_OBJECT

public:
    explicit ChatServerAdmin(QString = "", quint16 = 0,     // ChatServerAdmin 생성자
                             QWidget *parent = nullptr);
    ~ChatServerAdmin();                                     // ChatServerAdmin 소멸자

public slots:
    void clientChatRecv(QString,QString);                   // client로부터 메세지를 받으면실행되는 슬롯

private slots:
    void on_sendpushButton_clicked();                       // send버튼 클릭시 실행되는 슬롯

signals:
    void sendData(QString,QString);                         // 데이터를 보내기위한 시그널

private:
    Ui::ChatServerAdmin *ui;

    QString cname;
    quint16 port;
};

#endif // CHATSERVERADMIN_H
