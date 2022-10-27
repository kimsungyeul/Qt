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
    explicit ChatServerAdmin(QString = "", quint16 = 0, QWidget *parent = nullptr);
    ~ChatServerAdmin();

public slots:
    void clientChatRecv(QString,QString);

private slots:
    void on_sendpushButton_clicked();
    void on_quitpushButton_clicked();

signals:
    //void sendData(quint16,QString);
    void sendData(QString,QString);

private:
    Ui::ChatServerAdmin *ui;

    QString cname;
    quint16 port;
};

#endif // CHATSERVERADMIN_H
