#include "chatserver.h"
#include "ui_chatserver.h"
#include "logthread.h"
#include "chatserveradmin.h"
#include "chatnoticedetails.h"

#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QTcpServer>
#include <QTcpSocket>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QMenu>
#include <QScrollBar>

#include <QFile>
#include <QFileInfo>
#include <QProgressDialog>

ChatServer::ChatServer(QWidget *parent) :
    QWidget(parent), ui(new Ui::ChatServer), totalSize(0), byteReceived(0)
{
    ui->setupUi(this);

    QList<int> sizes;                                                       // TreeWidget과 ToolBox간 거리 조절용
    sizes << 200 << 600;                                                    // 사이즈 지정
    ui->splitter->setSizes(sizes);                                          // 사이즈 세팅

    chatServer = new QTcpServer(this);                                      // 채팅서버 객체생성
    connect(chatServer, SIGNAL(newConnection( )), SLOT(clientConnect( )));  // 채팅서버 연결용 시그널 슬롯
    if (!chatServer->listen(QHostAddress::Any, PORT_NUMBER)) {              // 서버연결이 안된다면 실행되는 messagebox
        QMessageBox::critical(this, tr("Chatting Server"), \
                              tr("Unable to start the server: %1.") \
                              .arg(chatServer->errorString( )));
        close( );
        return;
    }

    fileServer = new QTcpServer(this);                                      // 파일서버 생성
    connect(fileServer, SIGNAL(newConnection()), SLOT(acceptConnection())); // 파일서버 연결용 시그널 슬롯
    if (!fileServer->listen(QHostAddress::Any, PORT_NUMBER+1)) {            // 서버연결이 안된다면 실행되는 messagebox
        QMessageBox::critical(this, tr("Chatting Server"), \
                              tr("Unable to start the server: %1.") \
                              .arg(fileServer->errorString( )));
        close( );
        return;
    }

    qDebug("Start listening ...");

    QAction* inviteAction = new QAction(tr("&Invite"));                     // 초대용 액션 객체생성
    inviteAction->setObjectName("Invite");                                  // 초기 초대버튼활성화용
    connect(inviteAction, SIGNAL(triggered()), SLOT(inviteClient()));       // 초대버튼 클릭시 발동되는 연결슬롯

    QAction* removeAction = new QAction(tr("&Kick out"));                   // 강퇴용 액션 객체생성
    connect(removeAction, SIGNAL(triggered()), SLOT(kickOut()));            // 강퇴버튼 클릭시 발동되는 연결슬롯

    QAction*  privateChatAction = new QAction(tr("&Private Chat"));         // 1:1채팅용 액션 객체생성
    connect(privateChatAction, SIGNAL(triggered()),SLOT(privateChat()));    // 1:!채팅버튼 클릭시 발동되는 연결슬롯

    menu = new QMenu;                                                       // context메뉴를 사용하기위한 객체생성
    menu->addAction(inviteAction);                                          // 초대액션을 contextmenu에 추가
    ui->clientTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);      // clientTreeWidget내에서 위의 설정을 사용하기위함

    chatmenu = new QMenu;                                                   // context메뉴를 사용하기위한 객체생성
    chatmenu->addAction(privateChatAction);                                 // 1:1채팅액션을 contextmenu에 추가
    chatmenu->addAction(removeAction);                                      // 강퇴액션을 contextmenu에 추가
    ui->chatTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);        // chatTreeWidget내에서 위의 설정을 사용하기위함


    progressDialog = new QProgressDialog(0);                                // 0에서 시작하는 progressDialog 객체생성
    progressDialog->setAutoClose(true);                                     // 다이얼이 0 이면 자동으로 닫힌다
    progressDialog->reset();                                                // 다이얼로그 초기화

    logThread = new LogThread(this);                                        // 로그 저장을 위한 로그스레드 객체생성
    logThread->start();                                                     // 서버가 시작될 때 로그스레그 실행

    qDebug() << tr("The server is running on port %1.").arg(chatServer      //서버시작시 보여지는 qDebug 메시지
                                                            ->serverPort());
}

ChatServer::~ChatServer()                                                   // ChatServer 소멸자
{
    delete ui;

    logThread->terminate();                                                 // 로그스레드 종료
    chatServer->close( );                                                   // 채팅 서버 종료
    fileServer->close( );                                                   // 파일 서버 종료
}

void ChatServer::clientConnect( )                                           // 새로운 클라이언트가 연결될 때마다 연결멤버함수 실행
{
    QTcpSocket *clientConnection = chatServer->nextPendingConnection( );    // 데이터가 연결된다면 새로운 소켓생성
    connect(clientConnection, SIGNAL(readyRead( )), SLOT(receiveData( )));  // 클라이언트에서 보낸 데이터를 서버가 받기위한 connect
    connect(clientConnection, SIGNAL(disconnected( )), SLOT(removeClient()));   //서버와 클라이언트 연결이 끊길시 연결된 connect
    qDebug("new connection is established...");
}

void ChatServer::receiveData( )                                             // 클라이언트에서 받아오는 데이터 처리
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));   // 클라이언트에서 연결시 받아오는 sender
    QByteArray bytearray = clientConnection->read(BLOCK_SIZE);              // BLOCK_SIZE 만큼 읽어 bytearray에 저장

    Chat_Status type;                                                       // 채팅의 목적
    char data[1020];                                                        // 전송되는 메시지/데이터
    memset(data, 0, 1020);                                                  // 1020크기의 메모리데이터를 0으로 초기화

    QDataStream in(&bytearray, QIODevice::ReadOnly);                        // 입력용 데이터 스트림생성
    in.device()->seek(0);                                                   // 데이터스트림의 커서를 제일 앞 쪽으로 이동
    in >> type;                                                             // 프로토콜 타입 추출
    in.readRawData(data, 1020);                                             // 1020만큼의 데이터를 읽어옴

    QString ip = clientConnection->peerAddress().toString();                // 소켓과 연결된 address를 추출
    quint16 port = clientConnection->peerPort();                            // 소켓과 연결된 port 추출
    QString name = QString::fromStdString(data);                            // data의 이름을 추출

    auto finditem = ui->clientTreeWidget->findItems(name,                   // clientTreeWidget에 원하는 name검색
                                                    Qt::MatchFixedString, 1);
    auto findchatitem = ui->chatTreeWidget->findItems(name,                 // chatTreeWidget에 원하는 name 검색
                                                      Qt::MatchFixedString, 1);
    QTreeWidgetItem* saveitem = new QTreeWidgetItem;                        // 아이템 임시저장용 객체생성
    qDebug() << ip << " : " << type;                                        // 연결시 ip및 타입 확인용 qDebug

    switch(type) {                                                          // 프로토콜 타입에 따라 처리하기위한 swich-case문
    case Chat_Login: {                                                      // 프로토콜 타입이 Chat_Login이면
        if(finditem.count() == 0){                                          // 찾는 아이템이 없다면
            NonMemaddClient(name);                                          // 비회원멤버등록용 멤버함수에 이름전달
        } else {
            foreach(auto item, finditem) {                                  // fineitem의 item을 추출해
                if(item->text(0) != "-" && item->text(0) != "-b") {         // 현재상태 등록
                    item->setText(0, "-");
                }
            }
        }
        clientList.append(clientConnection);                                // QList<QTcpSocket*> clientList;
        clientSocketHash[name] = clientConnection;                          // Login단에서 이름을 key값으로 client포트에 바인드된 소켓포트값 및 데이터 저장
        portSocketHash[port] = clientConnection;                            // portSock용 해쉬
    }
        break;

    case Chat_In: {                                                         // 프로토콜 타입이 Chat_In이면
        foreach(auto item, finditem) {                                      // fineitem의 item을 추출해
            if(item->text(0) != "O" && item->text(0) != "-b") {             // 현재상태 등록
                item->setText(0, "O");                                      // 회원이면 O
            } else {
                item->setText(0, "Ob");                                     // 비회원이면 Ob
            }
            saveitem = item->clone();                                       // item을 임시저장
            clientNameHash[port] = name;                                    // 채팅입장시 Name Hash포트에 포트에따른 이름저장
            ui->clientTreeWidget->takeTopLevelItem(ui->clientTreeWidget     // clientTreeWidget의 항목 삭제
                                                   ->indexOfTopLevelItem(item));
            ui->clientTreeWidget->update();                                 // clientTreeWidget 업데이트
        }
        ui->chatTreeWidget->addTopLevelItem(saveitem);                      // 임시저장된 아이템을 chatTreeWidget에 항목추가
        ui->chatTreeWidget->resizeColumnToContents(0);                      // 자동으로 항목에따른 column사이즈 설정
    }
        break;
    case Chat_Talk: {                                                       // 프로토콜 타입이 Chat_Talk이면
        foreach(QTcpSocket *sock, clientList) {
            if(clientNameHash.contains(sock->peerPort())                    // clientList에 포함된 포트만 채팅되도록 설정
                    && sock != clientConnection){
                QByteArray sendArray;                                       // bytearray용 객체생성
                sendArray.clear();                                          // 생성한 bytearray데이터 초기화
                QDataStream out(&sendArray, QIODevice::WriteOnly);          // 출력용 데이터스트림 생성
                out << Chat_Talk;                                           // type데이터 설정
                sendArray.append("<font color=lightsteelblue>");            // type뒤에 보낼 데이터 설정(폰트컬러)
                sendArray.append(clientNameHash[port].toStdString().data());// type뒤에 보낼 데이터 설정(이름)
                sendArray.append("</font> : ");
                sendArray.append(name.toStdString().data());                // type뒤에 보낼 데이터 설정(내용)
                sock->write(sendArray);                                     // 위에 설정한 내용들을 보냄
            }
        }

        if (clientWindowHash.count() != 0) {                                // 1:1채팅창 띄워진게 하나라도 있다면
            clientWindowHash[clientNameHash[port]]                          // 이름에따른 개인채팅소켓을 저장
                    ->clientChatRecv(clientNameHash[port],data);
        }

        QTreeWidgetItem *logitem = new QTreeWidgetItem(ui->messageTreeWidget);  // logitem항목 추가용 객체생성
        logitem->setText(0, ip);                                                // 데이터를 전송한 소켓의 ip 주소
        logitem->setText(1, QString::number(port));                             // 데이터를 전송한 소켓의 port 번호
        logitem->setText(2, QString::number(clientIDHash[clientNameHash[port]]));// 데이터를 전송한 소켓의 클라이언트 id 번호
        logitem->setText(3, clientNameHash[port]);                              // 데이터를 전송한 소켓의 클라이언트 이름
        logitem->setText(4, QString(data));                                     // 데이터를 전송한 소켓의 데이터를 로그에 찍기
        logitem->setText(5, QDateTime::currentDateTime().toString());           // 로그 메시지가 길 경우 툴팁으로 표시
        logitem->setToolTip(4, QString(data));                                  // tooltip에 로그내용 추가

        for(int i = 0; i < ui->messageTreeWidget->columnCount(); i++)           // messageTreeWidget의 column의 사이즈를 자동으로 재조정
            ui->messageTreeWidget->resizeColumnToContents(i);

        ui->messageTreeWidget->addTopLevelItem(logitem);                        // messageTreeWidget에 로그 표시
        logThread->appendData(logitem);                                         // 로그 스레드에 로그 추가
    }
        break;
    case Chat_Out: {                                                            // 프로토콜 타입이 Chat_Out이면
        foreach(auto item, findchatitem) {                                      // findchatitem item을 추출해
            if(item->text(0) != "-" && item->text(0) != "Ob") {                 // 현재상태 등록
                item->setText(0, "-");                                          // 회원이면 -
            } else {
                item->setText(0, "-b");                                         // 비회원이면 -b
            }
            saveitem = item->clone();                                           // item을 임시저장
            clientNameHash.remove(port);                                        // clientNameHash의 port삭제
            ui->chatTreeWidget->takeTopLevelItem(ui->chatTreeWidget             // chatTreeWidget의 항목 삭제
                                                 ->indexOfTopLevelItem(item));
            ui->chatTreeWidget->update();                                       // chatTreeWidget 업데이트
        }
        ui->clientTreeWidget->addTopLevelItem(saveitem);                        // 임시저장된 아이템을 clientTreeWidget에 항목추가
        ui->clientTreeWidget->resizeColumnToContents(0);                        // 자동으로 항목에따른 column사이즈 설정
    }
        break;
    case Chat_LogOut:                                                           // 프로토콜 타입이 Chat_LogOut이면
        if (finditem.count() != 0) {                                            // finditem에 존재한다면
            foreach(auto item, finditem) {                                      // finditem 항목을 가져와
                if(item->text(0) != "X" && item->text(0) != "-b"                // 현재상태 초기화
                        && item->text(0) != "Ob") {
                    item->setText(0, "X");                                      // 회원이면 X로 표시
                } else {
                    ui->clientTreeWidget->takeTopLevelItem(ui->clientTreeWidget // 비회원이면 항목을삭제
                                                           ->indexOfTopLevelItem(item));
                    ui->clientTreeWidget->update();                             // clientTreeWidget 업데이트
                }
                clientList.removeOne(clientConnection);                         // QList<QTcpSocket*> clientList;
                clientSocketHash.remove(name);                                  // LogOut시 서버에 접속된 소켓 Data 삭제
                portSocketHash.remove(port);                                    // portSocketHash의 port삭제
            }
        } else {
            foreach(auto item, findchatitem) {                                  // finditem이 0이라면 findchatitem에서 항목가져와
                saveitem = item->clone();                                       // 임시저장용 아이템에 아이템복사
                if(item->text(0) != "X" && item->text(0) != "-b"                // 현제상태 초기화
                        && item->text(0) != "Ob") {
                    item->setText(0, "X");                                      // 회원이면 X로 표시
                    saveitem = item->clone();                                   // 임시저장용 아이템에 아이템복사
                    ui->chatTreeWidget->takeTopLevelItem(ui->chatTreeWidget     // chatTreeWidget에 항목삭제
                                                         ->indexOfTopLevelItem(item));
                    ui->chatTreeWidget->update();                               // chatTreeWidget 업데이트
                    ui->clientTreeWidget->addTopLevelItem(saveitem);            // clientTreeWidget에 항목추가
                } else {                                                        // 비회원이라면
                    ui->chatTreeWidget->takeTopLevelItem(ui->chatTreeWidget     // chatTreeWidget에서 item삭제
                                                         ->indexOfTopLevelItem(item));
                    ui->chatTreeWidget->update();                               // chatTreeWidget 업데이트
                }
                clientList.removeOne(clientConnection);                         // QList<QTcpSocket*> clientList;
                clientSocketHash.remove(name);                                  // LogOut시 서버에 접속된 소켓 Data 삭제
                portSocketHash.remove(port);                                    // portSocketHash의 port삭제
            }
        }
        break;
    }
}

void ChatServer::removeClient()                                                 // 클라이언트가 서버를 나갈때 함수
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));       // 서버를 나간 클라이언트 소켓 을 sender로 받아옴
    clientList.removeOne(clientConnection);                                     // clientList에서 소켓삭제
    clientConnection->deleteLater();                                            // 소켓이 삭제될때 발동
    QString name = clientNameHash[clientConnection->peerPort()];                // clientNameHash에서 name추출
    auto finditem = ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1);// clientTreeWidget원하는 name추출
    foreach(auto item, finditem) {                                              // finditem에 item검색
        if (finditem.count() != 0) {
            item->setText(0, "X");                                              // 현재상태를 X로 변경
        }
    }

    clientList.removeOne(clientConnection);                                     // clientList에서 소켓삭제
    clientConnection->deleteLater();                                            // 소켓이 삭제될때 발동
}

void ChatServer::addClient(int id, QString name)                                // clientmanager에서 등록or modify시 addclient slot발생
{
    clientIDList << id;                                                         // addclient에 받아온 id를 clientIdList에 등록
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->clientTreeWidget);          // ClientTreewidget에 선택한 아이템을 객체로 복사
    item->setText(0, "X");                                                      // 현재상태 X로 초기화
    item->setText(1, name);                                                     // name 세팅
    ui->clientTreeWidget->addTopLevelItem(item);                                // clientTreeWidget에 항목추가
    clientIDHash[name] = id;                                                    // clientIDHash에 이름에따른 id추가
    ui->clientTreeWidget->resizeColumnToContents(0);                            // clientTreeWidget에 항목 추가시 자등으로 column정렬
}

int ChatServer::makeNonId()                                                     // 비회원 아이디 등록
{
    if(clientIDList.size( ) == 0) {                                             // clientList에 등록이 안됫다면
        return 10000;                                                           // 10000번부터 id부여
    } else {                                                                    // clientList에 Id가 하나라도 잇다면
        auto id = clientIDList.back();                                          // clientList의 마지막값을가져와
        return ++id;                                                            // +1된 값으로 id 지정
    }
}

void ChatServer::NonMemaddClient(QString name)                                  // 비회원 이름등록
{
    int id = makeNonId();                                                       // 비회원 ID등록
    clientIDList << id;                                                         // clientIDList에 id등록
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->clientTreeWidget);          // clientTreeWidget에 item가져와 객체생성
    item->setText(0, "-b");                                                     // 비회원 처음등록후 -b상태 초기화
    item->setText(1, name);                                                     // 비회원 이름 초기화
    ui->clientTreeWidget->addTopLevelItem(item);                                // clientTreeWidget에 항목추가
    clientIDHash[name] = id;                                                    // clientIDHash에 이름에따른 id 추가
    ui->clientTreeWidget->resizeColumnToContents(0);                            // clientTreeWidget에 항목 추가시 자등으로 column정렬
}

void ChatServer::kickOut()                                                      // 클라이언트 강퇴
{
    if(ui->clientTreeWidget->currentItem() == nullptr) {                        // 선택된클라이언트가 없을시 리턴
        return;
    }

    if(ui->chatTreeWidget->topLevelItemCount()) {                               // chatTreeWidget에 항목이 존재한다면
        QString name = ui->chatTreeWidget->currentItem()->text(1);              // 선택된 항목의 이름을 name으로 등록
        QTcpSocket* sock = clientSocketHash[name];                              // sockethash에 이름에맞는 socket 데이터를 sock에 저장
        quint16 port = sock->peerPort();                                        // 소켓에포트를 등록
        QByteArray sendArray;                                                   // 보낼ByteArray 생성
        QDataStream out(&sendArray, QIODevice::WriteOnly);                      // 데이터 출력스트림 생성
        out << Chat_KickOut;                                                    // 첫번째 인자로 type입력
        out.writeRawData("", 1020);                                             // type data인 4비트 제외 1020데이터에 빈내용 입력

        sock->write(sendArray);                                                 // 소켓에 데이터를 써서 보냄

        auto findchatitem = ui->chatTreeWidget->findItems(name,                 // chatTreeWidget에서 원하는 name 찾기
                                                          Qt::MatchFixedString, 1);
        QTreeWidgetItem* saveitem;                                              // 임시등록용 item객체생성
        foreach (auto item, findchatitem) {                                     // 선택된 아이템 등록
            if(item->text(0) != "-" && item->text(0) != "Ob") {                 // 상태 초기화
                item->setText(0, "-");                                          // 회원이라면 -
            } else {
                item->setText(0, "-b");                                         // 비회원이라면 -b
            }
            saveitem = item->clone();                                           // item항목 복사
            clientNameHash.remove(port);                                        // clientNameHash에 port제거
            ui->chatTreeWidget->takeTopLevelItem(ui->chatTreeWidget             // chatTreeWidget 의 선택한 item 제거
                                                 ->indexOfTopLevelItem(item));
            ui->chatTreeWidget->update();                                       // chatTreeWidget 업데이트
        }
        ui->clientTreeWidget->addTopLevelItem(saveitem);                        // 복사된 item항목 clientTreeWidget에 등록
        ui->clientTreeWidget->resizeColumnToContents(0);                        // clientTreeWidget에 항목 추가시 자등으로 column정렬
    }
}

void ChatServer::inviteClient()                                                 // 클라이언트 초대
{
    if(ui->clientTreeWidget->currentItem() == nullptr ||                        // clientTreeWidget에 선택된아이템이 없다면
            ui->clientTreeWidget->currentItem()->text(0) == "X") {
        return;
    }

    if(ui->clientTreeWidget->topLevelItemCount()) {                             // clientTreeWidget에 아이템항목이 하나라도 잇다면
        QString name = ui->clientTreeWidget->currentItem()->text(1);            // clientTreeWidget의 이름을 가져와 등록
        QByteArray sendArray;                                                   // 데이터 출력용 변수선언
        QDataStream out(&sendArray, QIODevice::WriteOnly);                      // 데이터 출력용 스트림 생성
        out << Chat_Invite;                                                     // Chat_Invite의 첫인자로 입력
        out.writeRawData("", 1020);                                             // 나머지 1020비트 에 빈데이터 입력
        QTcpSocket* sock = clientSocketHash[name];                              // clientSocketHash에 이름으로 등록된 소켓가져옴
        quint16 port = sock->peerPort();                                        // 소켓에서 포트추출
        sock->write(sendArray);                                                 // iterator로 비교안해도 소켓에 바로쓰면됨
        auto finditem = ui->clientTreeWidget->findItems(name,                   // clientTreeWidget에 원하는 item찾기
                                                        Qt::MatchFixedString, 1);
        QTreeWidgetItem* saveitem = new QTreeWidgetItem;                        // 임시저장용 item 객체생성
        foreach (auto item, finditem) {                                         // 찾은 item정보 추출
            if(item->text(0) != "O" && item->text(0) != "-b") {                 // 상태 초기화
                item->setText(0, "O");                                          // 회원이면 O상태
            } else {
                item->setText(0, "Ob");                                         // 비회원이면 Ob상태
            }
            saveitem = item->clone();                                           // 임시저장객체에 복사
            ui->clientTreeWidget->takeTopLevelItem(ui->clientTreeWidget         // clientTreeWidget에 선택item 제거
                                                   ->indexOfTopLevelItem(item));
            ui->clientTreeWidget->update();                                     // clientTreeWidget항목 업데이트
        }
        clientNameHash[port] = name;                                            // clientNameHash에 포트로 이름등록
        ui->chatTreeWidget->addTopLevelItem(saveitem);                          // 임시생성item을 chatTreeWidget에 등록
        ui->chatTreeWidget->resizeColumnToContents(0);                          // clientNameHash에 항목 추가시 자등으로 column정렬
    }
}

void ChatServer::on_clientTreeWidget_customContextMenuRequested(const QPoint &pos)
{
    if(ui->clientTreeWidget->currentItem() == nullptr) {
        return;
    }

    QPoint globalPos = ui->clientTreeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void ChatServer::on_chatTreeWidget_customContextMenuRequested(const QPoint &pos)
{
    if(ui->chatTreeWidget->currentItem() == nullptr){
        return;
    }

    QPoint globalPos = ui->chatTreeWidget->mapToGlobal(pos);
    chatmenu->exec(globalPos);
}

void ChatServer::acceptConnection()
{
    qDebug("Connected, preparing to receive files!");

    QTcpSocket* receivedSocket = fileServer->nextPendingConnection();
    connect(receivedSocket, SIGNAL(readyRead()), this, SLOT(readClient()));
}

void ChatServer::readClient()                                   // 파일 읽기용 동작
{
    qDebug("Receiving file ...");
    QTcpSocket* receivedSocket = dynamic_cast<QTcpSocket *>(sender( ));
    QString filename;

    if (byteReceived == 0) { // just started to receive data, this data is file information
        progressDialog->reset();
        progressDialog->show();

        QString ip = receivedSocket->peerAddress().toString();
        quint16 port = receivedSocket->peerPort()-2;

        QDataStream in(receivedSocket);
        in >> totalSize >> byteReceived >> filename;
        progressDialog->setMaximum(totalSize);

        QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);
        item->setText(0, ip);
        item->setText(1, QString::number(port + 2));
        item->setText(2, QString::number(clientIDHash[clientNameHash[port]]));
        item->setText(3, clientNameHash[port]);
        item->setText(4, filename);
        item->setText(5, QDateTime::currentDateTime().toString());
        item->setToolTip(4, filename);

        for(int i = 0; i < ui->messageTreeWidget->columnCount(); i++)
            ui->messageTreeWidget->resizeColumnToContents(i);

        ui->messageTreeWidget->addTopLevelItem(item);

        logThread->appendData(item);

        QFileInfo info(filename);
        QString currentFileName = info.fileName();
        file = new QFile(currentFileName);
        file->open(QFile::WriteOnly);
    } else { // Officially read the file content
        inBlock = receivedSocket->readAll();

        byteReceived += inBlock.size();
        file->write(inBlock);
        file->flush();
    }

    progressDialog->setValue(byteReceived);

    if (byteReceived == totalSize) {
        qDebug() << QString("%1 receive completed").arg(filename);

        inBlock.clear();
        byteReceived = 0;
        totalSize = 0;
        progressDialog->reset();
        progressDialog->hide();
        file->close();
        delete file;
    }
}

void ChatServer::privateChat()                                      // 1:1채팅서버동작
{
    QString cname = ui->chatTreeWidget->currentItem()->text(1);
    QTcpSocket* sock = clientSocketHash[cname];
    quint16 port = sock->peerPort();
    ChatServerAdmin* Admin = new ChatServerAdmin(cname,port);
    clientWindowHash[cname] = Admin;
    //connect(Admin,SIGNAL(sendData(quint16,QString)), SLOT(privateChatSend(quint16,QString)));
    connect(Admin,SIGNAL(sendData(QString,QString)), SLOT(privateChatSend(QString,QString)));

    Admin->setWindowTitle("Prvate Chat");
    Admin->show();
}

void ChatServer::privateChatSend(QString name, QString str)
{
    QTcpSocket* sock = clientSocketHash[name];
    quint16 port = sock->peerPort();
    QByteArray sendArray;
    sendArray.clear();
    QDataStream out(&sendArray, QIODevice::WriteOnly);
    out << Chat_Talk;
    sendArray.append("<font color=blue>");
    sendArray.append("Admin");
    sendArray.append("</font> : ");
    sendArray.append(str.toStdString().data());
    sock->write(sendArray);


    QTreeWidgetItem *logitem = new QTreeWidgetItem(ui->messageTreeWidget);
    logitem->setText(1, QString::number(port));
    logitem->setText(2, "Admin");
    logitem->setText(3, "Admin");
    logitem->setText(4, str);
    logitem->setText(5, QDateTime::currentDateTime().toString());
    logitem->setToolTip(4, str);

    for(int i = 0; i < ui->messageTreeWidget->columnCount(); i++)
        ui->messageTreeWidget->resizeColumnToContents(i);

    ui->messageTreeWidget->addTopLevelItem(logitem);
}


void ChatServer::on_noticepushButton_clicked()
{
    if (clientNameHash.count() == 0) {
        QMessageBox::critical(this, tr("Notice Details"), \
                              tr("There isn't anybody in the ChatList."));
        return;
    }

    ui->noticepushButton->setEnabled(false);

    QList<QTreeWidgetItem*> clientnameList;


    ChatNoticeDetails* notice = new ChatNoticeDetails(clientnameList);

    connect(notice, SIGNAL(sendData(QString,QString)), SLOT(privateChatSend(QString,QString)));

    notice->setWindowTitle("Notice Chat");
    notice->show();
}

