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
class ChatNoticeDetails;

namespace Ui {
class ChatServer;
}

typedef enum {
    Chat_Login,                                         // 로그인(서버 접속)   --> 초대를 위한 정보 저장
    Chat_In,                                            // 채팅방 입장
    Chat_Talk,                                          // 채팅
    Chat_Out,                                           // 채팅방 퇴장         --> 초대 가능
    Chat_LogOut,                                        // 로그 아웃(서버 단절) --> 초대 불가능
    Chat_Invite,                                        // 초대
    Chat_KickOut,                                       // 강퇴
    Chat_Notice                                         // 공지
} Chat_Status;

class ChatServer : public QWidget
{
    Q_OBJECT

public:
    explicit ChatServer(QWidget *parent = nullptr);
    ~ChatServer();

public slots:
    void clientConnect();                              // 클라이언트 연결 슬롯함수
    void receiveData();                                // 클라이언트가 데이터를 받아 처리하는 슬롯함수
    void removeClient();                               // 클라이언트가 접속종료시 실행되는 슬롯함수
    void addClient(int, QString);                       // Client초기 고객목록설정
    int makeNonId();                                    // 미등록고객Id부여
    void NonMemaddClient(QString);                      // 미등록고객 멤버설정
    void inviteClient();                                // 고객초대용 슬롯
    void kickOut();                                     // 고객강퇴용 슬롯

    void acceptConnection();                            // 파일서버 연결확인용 슬롯
    void readClient();                                  // 파일서버 read확인용 슬롯

    void privateChat();                                 // 1:1채팅 구현용 슬롯
    void privateChatSend(QString,QString);              // 1:1채팅유형 등록 슬롯

private slots:
    // clientTreeWidget에 우클릭선택시 실행되는 슬롯
    void on_clientTreeWidget_customContextMenuRequested(const QPoint &pos);
    // chatTreeWidget에 우클릭선택시 실행되는 슬롯
    void on_chatTreeWidget_customContextMenuRequested(const QPoint &pos);

    void on_noticepushButton_clicked();                 // notice버튼 클릭스 실행되는 슬롯

private:
    const int BLOCK_SIZE = 1024;                        // BLOCK_SIZE = 1024 고정
    const int PORT_NUMBER = 8000;                       // PORT_NUMBER = 8000 고정

    Ui::ChatServer *ui;
    QTcpServer *chatServer;                             // 채팅 서버

    QList<QTcpSocket*> clientList;                      // 채팅 서버
    QList<int> clientIDList;
    QList<QString> chatList;

    QHash<quint16, QString> clientNameHash;             // 포트번호로 고객이름을 찾기위함
    QHash<QString, QTcpSocket*> clientSocketHash;       // 고객이름으로 소켓을찾기위함
    QHash<QString, int> clientIDHash;                   // 고객이름으로 ID를 찾기위함
    QHash<quint16, QTcpSocket*> portSocketHash;         // 포트번호로 소켓을 찾기위함
    QHash<QString, ChatServerAdmin*> clientWindowHash;  // 이름으로 Window창을 찾기 위함
    QMenu* menu;
    QMenu* chatmenu;

    QTcpServer *fileServer;                             // 파일서버
    QFile* file;                                        // 파일 전송을 위한 파일 객체
    QProgressDialog* progressDialog;                    // 파일 전송 현황을 보기 위한 프로그레스 다이얼로그
    qint64 totalSize;                                   // 전체 파일 크기
    qint64 byteReceived;                                // 현재 받을 파일 크기
    QByteArray inBlock;                                 // 받은 파일을 바이트어레이 형태로 저장
    LogThread* logThread;                               // 로그 스레드
};

#endif // CHATSERVER_H
