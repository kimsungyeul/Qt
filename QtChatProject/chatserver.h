#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QWidget>
#include <QList>
#include <QHash>

class QLabel;
class QTcpServer;
class QTcpSocket;

namespace Ui {
class ChatServer;
}

typedef enum {
    Chat_Login,             // 로그인(서버 접속)   --> 초대를 위한 정보 저장
//    Chat_LoginCheck,        // 고객 확인
    Chat_In,                // 채팅방 입장
    Chat_Talk,              // 채팅
    Chat_Close,             // 채팅방 퇴장         --> 초대 가능
    Chat_LogOut,            // 로그 아웃(서버 단절) --> 초대 불가능
    Chat_Invite,            // 초대
    Chat_KickOut,           // 강퇴
    Chat_FileTrans_Start,   // 파일 전송 시작(파일명) --> 파일 오픈
    Chat_FileTransfer,      // 파일 데이터 전송      --> 데이터를 파일에 저장
    Chat_FileTrans_End,     // 파일 전송 완료        --> 파일 닫기
} Chat_Status;

typedef struct {            // 채팅 프로토콜 설계
    Chat_Status type;       // 채팅의 목적
    char data[1020];        // 전송되는 메시지/데이터
} chatProtocolType;

class ChatServer : public QWidget
{
    Q_OBJECT

public:
    explicit ChatServer(QWidget *parent = nullptr);
    ~ChatServer();

signals:
    void clientNameDataSent();

public slots:
    void clientConnect( );                       /* 에코(채팅) 서버 */
    void echoData( );
    void removeClient( );
    void addClient(int, QString);
    void kickOut();
    void inviteClient();
    void on_clientTreeWidget_customContextMenuRequested(const QPoint &pos);

private:
    int nameDataWidgetflag = 0;

    const int BLOCK_SIZE = 1024;
    Ui::ChatServer *ui;
    QTcpServer *tcpServer;
    QList<QTcpSocket*> clientList;
    QList<int> clientIDList;
    QHash<QString, QString> clientNameHash;
    QHash<QString, int> clientIDHash;
    QMenu* menu;

//    QList<QTcpSocket*> clientCheckList;
//    QHash<QString, QString> clientNameCheckHash;
};

#endif // CHATSERVER_H
