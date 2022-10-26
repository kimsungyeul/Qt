#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QWidget>
#include <QList>
#include <QHash>

class QLabel;
class QTcpServer;
class QTcpSocket;

class QFile;
class QProgressDialog;
class LogThread;

namespace Ui {
class ChatServer;
}

typedef enum {
    Chat_Login,             // 로그인(서버 접속)   --> 초대를 위한 정보 저장
//    Chat_LoginCheck,        // 고객 확인
    Chat_In,                // 채팅방 입장
    Chat_Talk,              // 채팅
    Chat_Out,             // 채팅방 퇴장         --> 초대 가능
    Chat_LogOut,            // 로그 아웃(서버 단절) --> 초대 불가능
    Chat_Invite,            // 초대
    Chat_KickOut,           // 강퇴
//    Chat_FileTrans_Start,   // 파일 전송 시작(파일명) --> 파일 오픈
//    Chat_FileTransfer,      // 파일 데이터 전송      --> 데이터를 파일에 저장
//    Chat_FileTrans_End,     // 파일 전송 완료        --> 파일 닫기
} Chat_Status;

//typedef struct {            // 채팅 프로토콜 설계
//    Chat_Status type;       // 채팅의 목적
//    char data[1020];        // 전송되는 메시지/데이터
//} chatProtocolType;

class ChatServer : public QWidget
{
    Q_OBJECT

public:
    explicit ChatServer(QWidget *parent = nullptr);
    ~ChatServer();

private slots:
    void clientConnect( );                       /* 에코(채팅) 서버 */
    void receiveData( );
    void removeClient( );
    void addClient(int, QString);
    int makeNonId();
    void NonMemaddClient(QString);
    void inviteClient();
    void kickOut();
    void on_clientTreeWidget_customContextMenuRequested(const QPoint &pos);

    void acceptConnection();                    /* 파일 서버 */
    void readClient();

    void on_chatTreeWidget_customContextMenuRequested(const QPoint &pos);

private:
    const int BLOCK_SIZE = 1024;
    const int PORT_NUMBER = 8000;

    Ui::ChatServer *ui;
    QTcpServer *chatServer;

    QList<QTcpSocket*> clientList;
    QList<int> clientIDList;
    QAction* inviteAction;
//    QHash<QString, QString> clientNameHash;
//    QHash<QString, int> clientIDHash;
    QHash<quint16, QString> clientNameHash;
    QHash<QString, QTcpSocket*> clientSocketHash;
    QHash<QString, int> clientIDHash;
    QMenu* menu;

    QTcpServer *fileServer;
    QFile* file;
    QProgressDialog* progressDialog;
    qint64 totalSize;
    qint64 byteReceived;
    QByteArray inBlock;
    LogThread* logThread;

//    QList<QTcpSocket*> clientCheckList;
//    QHash<QString, QString> clientNameCheckHash;
};

#endif // CHATSERVER_H
