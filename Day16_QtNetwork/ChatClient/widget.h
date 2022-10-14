#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QTextEdit;
class QLineEdit;
class QTcpSocket;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void echoData( );			// 서버에서 데이터가 올 때
    void sendData( );			// 서버로 데이터를 보낼 때

private:
    QTextEdit *message;		// 서버에서 오는 메세지 표시용
    QLineEdit *inputLine;		// 서버로 보내는 메시지 입력용
    QTcpSocket *clientSocket;		// 클라이언트용 소켓
};
#endif // WIDGET_H
