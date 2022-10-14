#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>

class QLabel;
class QTcpServer;
class QTcpSocket;

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void clientConnect( );                       /* 에코 서버 */
    void echoData( );
    void removeItem( );

private:
    QLabel *infoLabel;
    QTcpServer *tcpServer;

    QList<QTcpSocket*> clientList;
};

#endif // WIDGET_H
