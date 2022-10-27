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
class ChatServerAdmin;

namespace Ui {
class ChatServer;
}

typedef enum {
    Chat_Login,             // 로그인(서버 접속)   --> 초대를 위한 정보 저장
    Chat_In,                // 채팅방 입장
    Chat_Talk,              // 채팅
    Chat_Out,             // 채팅방 퇴장         --> 초대 가능
    Chat_LogOut,            // 로그 아웃(서버 단절) --> 초대 불가능
    Chat_Invite,            // 초대
    Chat_KickOut,           // 강퇴
} Chat_Status;

class ChatServer : public QWidget
{
    Q_OBJECT

public:
    explicit ChatServer(QWidget *parent = nullptr);
    ~ChatServer();

public slots:
    void clientConnect( );                       /* 에코(채팅) 서버 */
    void receiveData( );
    void removeClient( );
    void addClient(int, QString);
    int makeNonId();
    void NonMemaddClient(QString);
    void inviteClient();
    void kickOut();

    void acceptConnection();                    /* 파일 서버 */
    void readClient();

    void privateChat();

private slots :
    void on_clientTreeWidget_customContextMenuRequested(const QPoint &pos);
    void on_chatTreeWidget_customContextMenuRequested(const QPoint &pos);

private:
    const int BLOCK_SIZE = 1024;
    const int PORT_NUMBER = 8000;

    Ui::ChatServer *ui;
    QTcpServer *chatServer;

    QList<QTcpSocket*> clientList;
    QList<int> clientIDList;
    QHash<quint16, QString> clientNameHash;
    QHash<QString, QTcpSocket*> clientSocketHash;
    QHash<QString, int> clientIDHash;
    QMenu* menu;
    QMenu* chatmenu;

    QTcpServer *fileServer;
    QFile* file;
    QProgressDialog* progressDialog;
    qint64 totalSize;
    qint64 byteReceived;
    QByteArray inBlock;
    LogThread* logThread;
};

#endif // CHATSERVER_H
