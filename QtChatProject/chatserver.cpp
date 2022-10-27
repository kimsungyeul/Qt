#include "chatserver.h"
#include "ui_chatserver.h"
#include "logthread.h"
#include "chatserveradmin.h"

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

    QList<int> sizes;
    sizes << 200 << 600;
    ui->splitter->setSizes(sizes);

    chatServer = new QTcpServer(this);
    connect(chatServer, SIGNAL(newConnection( )), SLOT(clientConnect( )));
    if (!chatServer->listen(QHostAddress::Any, PORT_NUMBER)) {
        QMessageBox::critical(this, tr("Chatting Server"), \
                              tr("Unable to start the server: %1.") \
                              .arg(chatServer->errorString( )));
        close( );
        return;
    }

    /* 파일서버 생성*/
    fileServer = new QTcpServer(this);
    connect(fileServer, SIGNAL(newConnection()), SLOT(acceptConnection()));
    if (!fileServer->listen(QHostAddress::Any, PORT_NUMBER+1)) {
        QMessageBox::critical(this, tr("Chatting Server"), \
                              tr("Unable to start the server: %1.") \
                              .arg(fileServer->errorString( )));
        close( );
        return;
    }

    qDebug("Start listening ...");

    QAction* inviteAction = new QAction(tr("&Invite"));
    inviteAction->setObjectName("Invite");
    connect(inviteAction, SIGNAL(triggered()), SLOT(inviteClient()));

    QAction* removeAction = new QAction(tr("&Kick out"));
    connect(removeAction, SIGNAL(triggered()), SLOT(kickOut()));

    QAction*  privateChatAction = new QAction(tr("&Private Chat"));
    connect(privateChatAction, SIGNAL(triggered()),SLOT(privateChat()));

    menu = new QMenu;
    menu->addAction(inviteAction);
    ui->clientTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    chatmenu = new QMenu;
    chatmenu->addAction(privateChatAction);
    chatmenu->addAction(removeAction);
    ui->chatTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    progressDialog = new QProgressDialog(0);
    progressDialog->setAutoClose(true);
    progressDialog->reset();

    logThread = new LogThread(this);
    logThread->start();

    qDebug() << tr("The server is running on port %1.").arg(chatServer->serverPort());
}

ChatServer::~ChatServer()
{
    delete ui;

    logThread->terminate();
    chatServer->close( );
    fileServer->close( );
}

void ChatServer::clientConnect( )
{
    QTcpSocket *clientConnection = chatServer->nextPendingConnection( );
    connect(clientConnection, SIGNAL(readyRead( )), SLOT(receiveData( )));
    connect(clientConnection, SIGNAL(disconnected( )), SLOT(removeClient()));
    qDebug("new connection is established...");
}

void ChatServer::receiveData( )
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));
    QByteArray bytearray = clientConnection->read(BLOCK_SIZE);

    //chatProtocolType data;
    Chat_Status type;       // 채팅의 목적
    char data[1020];        // 전송되는 메시지/데이터
    memset(data, 0, 1020);

    QDataStream in(&bytearray, QIODevice::ReadOnly);
    in.device()->seek(0);
    in >> type;
    in.readRawData(data, 1020);

    QString ip = clientConnection->peerAddress().toString();
    quint16 port = clientConnection->peerPort();
    QString name = QString::fromStdString(data);

    auto finditem = ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1);
    auto findchatitem = ui->chatTreeWidget->findItems(name, Qt::MatchFixedString, 1);
    QTreeWidgetItem* saveitem = new QTreeWidgetItem;
    qDebug() << ip << " : " << type;

    switch(type) {
    case Chat_Login: {
        if(finditem.count() == 0){
            NonMemaddClient(name);
        } else {
            foreach(auto item, finditem) {
                if(item->text(0) != "-" && item->text(0) != "-b") {
                    item->setText(0, "-");
                }
            }
        }
        clientList.append(clientConnection);        // QList<QTcpSocket*> clientList;
        clientSocketHash[name] = clientConnection;  // Login단에서 이름을 key값으로 client포트에 바인드된 소켓포트값 및 데이터 저장
        portSocketHash[port] = clientConnection;
    }
        break;

    case Chat_In: {
        foreach(auto item, finditem) {
            if(item->text(0) != "O" && item->text(0) != "-b") {
                item->setText(0, "O");
            } else {
                item->setText(0, "Ob");
            }
            saveitem = item->clone();
            clientNameHash[port] = name;            // 채팅입장시 Name Hash포트에 포트에따른 이름저장
            ui->clientTreeWidget->takeTopLevelItem(ui->clientTreeWidget->indexOfTopLevelItem(item));
            ui->clientTreeWidget->update();
        }
        ui->chatTreeWidget->addTopLevelItem(saveitem);
        ui->chatTreeWidget->resizeColumnToContents(0);
    }
        break;
    case Chat_Talk: {
        foreach(QTcpSocket *sock, clientList) {
            //if(clientNameHash.contains(sock->peerPort()) && sock != clientConnection){   // clientList에 포함된 포트만 채팅되도록 설정
            if(clientNameHash.contains(sock->peerPort())){
                QByteArray sendArray;
                sendArray.clear();
                QDataStream out(&sendArray, QIODevice::WriteOnly);
                out << Chat_Talk;
                sendArray.append("<font color=lightsteelblue>");
                sendArray.append(clientNameHash[port].toStdString().data());
                sendArray.append("</font> : ");
                sendArray.append(name.toStdString().data());
                sock->write(sendArray);
                qDebug() << sock->peerPort();
            }
        }
        if (clientWindowHash.count() != 0) {\
            clientWindowHash[clientNameHash[port]]->clientChatRecv(clientNameHash[port],data);
        }

        QTreeWidgetItem *logitem = new QTreeWidgetItem(ui->messageTreeWidget);
        logitem->setText(0, ip);
        logitem->setText(1, QString::number(port));
        logitem->setText(2, QString::number(clientIDHash[clientNameHash[port]]));                       /* ing */
        logitem->setText(3, clientNameHash[port]);
        logitem->setText(4, QString(data));
        logitem->setText(5, QDateTime::currentDateTime().toString());
        logitem->setToolTip(4, QString(data));

        for(int i = 0; i < ui->messageTreeWidget->columnCount(); i++)
            ui->messageTreeWidget->resizeColumnToContents(i);

        ui->messageTreeWidget->addTopLevelItem(logitem);

        logThread->appendData(logitem);
    }
        break;
    case Chat_Out: {
        foreach(auto item, findchatitem) {
            if(item->text(0) != "-" && item->text(0) != "Ob") {
                item->setText(0, "-");
            } else {
                item->setText(0, "-b");
            }
            saveitem = item->clone();
            clientNameHash.remove(port);
            ui->chatTreeWidget->takeTopLevelItem(ui->chatTreeWidget->indexOfTopLevelItem(item));
            ui->chatTreeWidget->update();
        }
        ui->clientTreeWidget->addTopLevelItem(saveitem);
        ui->clientTreeWidget->resizeColumnToContents(0);
    }
        break;
    case Chat_LogOut:
        if (finditem.count() != 0) {
            foreach(auto item, finditem) {
                if(item->text(0) != "X" && item->text(0) != "-b" && item->text(0) != "Ob") {
                    item->setText(0, "X");
                } else {
                    ui->clientTreeWidget->takeTopLevelItem(ui->clientTreeWidget->indexOfTopLevelItem(item));
                    ui->clientTreeWidget->update();
                }
                clientList.removeOne(clientConnection);        // QList<QTcpSocket*> clientList;
                clientSocketHash.remove(name);             // LogOut시 서버에 접속된 소켓 Data 삭제
                portSocketHash.remove(port);
            }
        } else {
            foreach(auto item, findchatitem) {
                saveitem = item->clone();
                if(item->text(0) != "X" && item->text(0) != "-b" && item->text(0) != "Ob") {
                    item->setText(0, "X");
                    saveitem = item->clone();
                    ui->chatTreeWidget->takeTopLevelItem(ui->chatTreeWidget->indexOfTopLevelItem(item));
                    ui->chatTreeWidget->update();
                    ui->clientTreeWidget->addTopLevelItem(saveitem);
                } else {
                    ui->chatTreeWidget->takeTopLevelItem(ui->chatTreeWidget->indexOfTopLevelItem(item));
                    ui->chatTreeWidget->update();
                }
                clientList.removeOne(clientConnection);        // QList<QTcpSocket*> clientList;
                clientSocketHash.remove(name);             // LogOut시 서버에 접속된 소켓 Data 삭제
                portSocketHash.remove(port);
            }
        }
        break;
    }
}

void ChatServer::removeClient()
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));
    clientList.removeOne(clientConnection);
    clientConnection->deleteLater();
    QString name = clientNameHash[clientConnection->peerPort()];
    auto finditem = ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1);
    foreach(auto item, finditem) {
        if (finditem.count() != 0) {
            item->setText(0, "X");
        }
    }

    clientList.removeOne(clientConnection);
    clientConnection->deleteLater();
}

void ChatServer::addClient(int id, QString name)
{
    clientIDList << id;
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->clientTreeWidget);
    item->setText(0, "X");
    item->setText(1, name);
    ui->clientTreeWidget->addTopLevelItem(item);
    clientIDHash[name] = id;
    ui->clientTreeWidget->resizeColumnToContents(0);
}

int ChatServer::makeNonId()
{
    if(clientIDList.size( ) == 0) {
        return 10000;
    } else {
        auto id = clientIDList.back();
        return ++id;
    }
}

void ChatServer::NonMemaddClient(QString name)
{
    int id = makeNonId();
    clientIDList << id;
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->clientTreeWidget);
    item->setText(0, "-b");
    item->setText(1, name);
    ui->clientTreeWidget->addTopLevelItem(item);
    clientIDHash[name] = id;
    ui->clientTreeWidget->resizeColumnToContents(0);
}

void ChatServer::kickOut()
{
    if(ui->clientTreeWidget->currentItem() == nullptr) {
        return;
    }

    if(ui->chatTreeWidget->topLevelItemCount()) {
        QString name = ui->chatTreeWidget->currentItem()->text(1);
        QTcpSocket* sock = clientSocketHash[name];          // sockethash에 이름에맞는 socket 데이터를 sock에 저장
        quint16 port = sock->peerPort();
        QByteArray sendArray;
        QDataStream out(&sendArray, QIODevice::WriteOnly);
        out << Chat_KickOut;
        out.writeRawData("", 1020);

        sock->write(sendArray);                             // 아래코드처럼 궂이 안찾아도 바로 찾은 소켓에 쓰면됨

        auto findchatitem = ui->chatTreeWidget->findItems(name, Qt::MatchFixedString, 1);
        QTreeWidgetItem* saveitem;
        foreach (auto item, findchatitem) {
            if(item->text(0) != "-" && item->text(0) != "Ob") {
                item->setText(0, "-");
            } else {
                item->setText(0, "-b");
            }
            saveitem = item->clone();
            clientNameHash.remove(port);
            ui->chatTreeWidget->takeTopLevelItem(ui->chatTreeWidget->indexOfTopLevelItem(item));
            ui->chatTreeWidget->update();
        }
        ui->clientTreeWidget->addTopLevelItem(saveitem);
        ui->clientTreeWidget->resizeColumnToContents(0);
    }
}

void ChatServer::inviteClient()
{
    if(ui->clientTreeWidget->currentItem() == nullptr ||
            ui->clientTreeWidget->currentItem()->text(0) == "X") {
        return;
    }
    if(ui->clientTreeWidget->topLevelItemCount()) {
        QString name = ui->clientTreeWidget->currentItem()->text(1);
        //quint16 port = clientNameHash.key(name, -1);      //포트비교를위해 선언하였으나 소켓Hash에서 이름검색후 바로 쓰면되므로 삭제

        //chatProtocolType data;
        QByteArray sendArray;
        QDataStream out(&sendArray, QIODevice::WriteOnly);
        out << Chat_Invite;
        out.writeRawData("", 1020);
        QTcpSocket* sock = clientSocketHash[name];
        quint16 port = sock->peerPort();
        sock->write(sendArray);                 // iterator로 비교안해도 소켓에 바로쓰면됨
        auto finditem = ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1);
        qDebug() << "5";
        QTreeWidgetItem* saveitem = new QTreeWidgetItem;
        qDebug() << "6";
        foreach (auto item, finditem) {
            if(item->text(0) != "O" && item->text(0) != "-b") {
                item->setText(0, "O");
            } else {
                item->setText(0, "Ob");
            }
            saveitem = item->clone();
            ui->clientTreeWidget->takeTopLevelItem(ui->clientTreeWidget->indexOfTopLevelItem(item));
            ui->clientTreeWidget->update();
        }
        clientNameHash[port] = name;
        ui->chatTreeWidget->addTopLevelItem(saveitem);
        ui->chatTreeWidget->resizeColumnToContents(0);
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

void ChatServer::readClient()
{
    qDebug("Receiving file ...");
    QTcpSocket* receivedSocket = dynamic_cast<QTcpSocket *>(sender( ));
    QString filename;

    if (byteReceived == 0) { // just started to receive data, this data is file information
        progressDialog->reset();
        progressDialog->show();

        QString ip = receivedSocket->peerAddress().toString();
        quint16 port = receivedSocket->peerPort();

        QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);
        item->setText(0, ip);
        item->setText(1, QString::number(port));
        item->setText(2, QString::number(clientIDHash[clientNameHash[port]]));
        item->setText(3, clientNameHash[port]);
        item->setText(4, filename);
        item->setText(5, QDateTime::currentDateTime().toString());
        item->setToolTip(4, filename);

        for(int i = 0; i < ui->messageTreeWidget->columnCount(); i++)
            ui->messageTreeWidget->resizeColumnToContents(i);

        ui->messageTreeWidget->addTopLevelItem(item);

        logThread->appendData(item);

        QDataStream in(receivedSocket);
        in >> totalSize >> byteReceived >> filename;
        progressDialog->setMaximum(totalSize);

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

void ChatServer::privateChat()
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

//void ChatServer::privateChatSend(quint16 port, QString str)
void ChatServer::privateChatSend(QString name, QString str)
{
    foreach(auto item, ui->chatTreeWidget->findItems(name, Qt::MatchFixedString, 1))
    {
        QString name = item->text(1);
        QString ip = QString::number(clientIDHash[name]);
        QTcpSocket* sock = clientSocketHash[name];
        QByteArray sendArray;
        sendArray.clear();
        QDataStream out(&sendArray, QIODevice::WriteOnly);
        out << Chat_Talk;
        sendArray.append("<font color=lightsteelblue>");
        sendArray.append(name.toStdString().data());
        sendArray.append("</font> : ");
        sendArray.append(str.toStdString().data());
        sock->write(sendArray);
    }
}
