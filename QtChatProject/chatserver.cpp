#include "chatserver.h"
#include "ui_chatserver.h"
#include "logthread.h"

#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QTcpServer>
#include <QTcpSocket>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <time.h>
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

    menu = new QMenu;
    menu->addAction(inviteAction);
    menu->addAction(removeAction);
    ui->clientTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

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
    connect(clientConnection, SIGNAL(disconnected( )), SLOT(removeItem()));
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

    qDebug() << ip << " : " << type;

    switch(type) {
    case Chat_Login:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            if(item->text(0) != "-") {
                item->setText(0, "-");
                clientList.append(clientConnection);        // QList<QTcpSocket*> clientList;
                clientNameHash[port] = name;
                clientIPHash[ip] = name;
            }
        }
        // Log check test code
//        auto finditem = ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1);

//        if(finditem.count() == 0) {
//            QString name = ui->clientTreeWidget->currentItem()->text(1);
//            QString ip = clientNameHash.key(name);

//            chatProtocolType data;
//            data.type = Chat_LoginCheck;

//            qstrcpy(data.data, "");
//            QByteArray sendArray;
//            QDataStream out(&sendArray, QIODevice::WriteOnly);
//            out << data.type;
//            out.writeRawData(data.data, 1020);
//            QTcpSocket* sock;
//            sock->write(sendArray);
//            foreach(QTcpSocket* sock, clientList) {
//                if(sock->peerAddress().toString() == ip){
//        //            sock->disconnectFromHost();
//                    sock->write(sendArray);
//                }
//            }
//        } else {
//            foreach(auto item, finditem) {
//                if(item->text(0) != "O") {
//                    item->setText(0, "O");
//                    clientList.append(clientConnection);        // QList<QTcpSocket*> clientList;
//                    clientNameHash[ip] = name;
//                }
//            }
//        }
        break;
//    case Chat_LoginCheck:

    case Chat_In:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
            if(item->text(0) != "O") {
                item->setText(0, "O");
            }
        }
        break;
    case Chat_Talk: {
        foreach(QTcpSocket *sock, clientList) {
            if(sock != clientConnection){
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
        qDebug()<<"1";
        ui->messageTreeWidget->addTopLevelItem(logitem);
        qDebug()<<"2";
        logThread->appendData(logitem);
    }
        break;
    case Chat_Out:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
            if(item->text(0) != "-") {
                item->setText(0, "-");
            }
        }
        break;
    case Chat_LogOut:
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
            if(item->text(0) != "X") {
                item->setText(0, "X");
                clientList.removeOne(clientConnection);        // QList<QTcpSocket*> clientList;
                clientNameHash.remove(port);
                clientIPHash.remove(ip);
            }
        }
        //        ui->inviteComboBox->addItem(name);
        break;
    }
}

void ChatServer::removeClient()
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));
    clientList.removeOne(clientConnection);
    clientConnection->deleteLater();

    QString name = clientNameHash[clientConnection->peerPort()];
    foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {
        item->setText(0, "X");
    }
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

void ChatServer::kickOut()
{
    QString name = ui->clientTreeWidget->currentItem()->text(1);
    QString ip = clientIPHash.key(name);

//    chatProtocolType data;
    QByteArray sendArray;
    QDataStream out(&sendArray, QIODevice::WriteOnly);
    out << Chat_KickOut;
    out.writeRawData("", 1020);

    foreach(QTcpSocket* sock, clientList) {
        if(sock->peerAddress().toString() == ip){
//            sock->disconnectFromHost();
            sock->write(sendArray);
        }
    }
    ui->clientTreeWidget->currentItem()->setText(0, "-");
//    clientIDList.append(clientIDHash[name]);
//    ui->inviteComboBox->addItem(name);
}

void ChatServer::inviteClient()
{
    if(ui->clientTreeWidget->topLevelItemCount()) {
        QString name = ui->clientTreeWidget->currentItem()->text(1);
        quint16 port = clientNameHash.key(name, -1);

        //chatProtocolType data;
        QByteArray sendArray;
        QDataStream out(&sendArray, QIODevice::WriteOnly);
        out << Chat_Invite;
        out.writeRawData("", 1020);

        foreach(QTcpSocket* sock, clientList) {
            if(sock->peerPort() == port){
                sock->write(sendArray);
                foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {
                    if(item->text(0) != "O") {
                        item->setText(0, "O");
                        clientList.append(sock);        // QList<QTcpSocket*> clientList;
//                        clientNameHash[ip] = name;
                    }
                }
            }
        }
    }
}

void ChatServer::on_clientTreeWidget_customContextMenuRequested(const QPoint &pos)
{
    foreach(QAction *action, menu->actions()) {
            if(action->objectName() == "Invite")
                action->setEnabled(ui->clientTreeWidget->currentItem()->text(0) != "O");
            else
                action->setEnabled(ui->clientTreeWidget->currentItem()->text(0) == "O");
        }
        QPoint globalPos = ui->clientTreeWidget->mapToGlobal(pos);
        menu->exec(globalPos);
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

        QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);
        item->setText(0, ip);
        item->setText(1, QString::number(receivedSocket->peerPort()));
        item->setText(2, QString::number(clientIDHash[clientIPHash[ip]]));
        item->setText(3, clientIPHash[ip]);
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
