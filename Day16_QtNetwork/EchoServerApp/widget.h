#ifndef WIDGET_H
#define WIDGET_H

#include <QLabel>
#include <QPushButton>
#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

private slots:
    void clientConnect();       /* 에코 서버 */
    void echoData();
    void removeItem();
private:
    QLabel *infoLabel;
    QTcpServer *tcpServer;

    QList<QTcpSocket*> clientList;
};
#endif // WIDGET_H
