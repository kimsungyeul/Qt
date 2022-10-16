#include "clientmanagerform.h"
#include "ui_clientmanagerform.h"
#include "clientitem.h"

#include <QFile>
#include <QMenu>

ClientManagerForm::ClientManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManagerForm)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 320 << 600;
    ui->splitter->setSizes(sizes);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->clienttreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->clienttreeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));

    QFile file("clientlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size()) {
            int id = row[0].toInt();
            ClientItem* c = new ClientItem(id, row[1], row[2], row[3]);
            ui->clienttreeWidget->addTopLevelItem(c);
            clientList.insert(id, c);

            emit clientAdded(row[1]);
        }
    }
    file.close( );
}

void ClientManagerForm::loadData()
{
//    QFile file("clientlist.txt");
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;

//    QTextStream in(&file);
//    while (!in.atEnd()) {
//        QString line = in.readLine();
//        QList<QString> row = line.split(", ");
//        if(row.size()) {
//            int id = row[0].toInt();
//            ClientItem* c = new ClientItem(id, row[1], row[2], row[3]);
//            ui->treeWidget->addTopLevelItem(c);
//            clientList.insert(id, c);

//            emit clientAdded(row[1]);
//        }
//    }
//    file.close( );
}

ClientManagerForm::~ClientManagerForm()
{
    delete ui;

    QFile file("clientlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const auto& v : clientList) {
        ClientItem* c = v;
        out << c->id() << ", " << c->getName() << ", ";
        out << c->getPhoneNumber() << ", ";
        out << c->getAddress() << "\n";
    }
    file.close( );
}

int ClientManagerForm::makeId( )
{
    if(clientList.size( ) == 0) {
        return 0;
    } else {
        auto id = clientList.lastKey();
        return ++id;
    }
}

void ClientManagerForm::removeItem()
{
    QTreeWidgetItem* item = ui->clienttreeWidget->currentItem();
    if(item != nullptr) {
        clientList.remove(item->text(0).toInt());
        ui->clienttreeWidget->takeTopLevelItem(ui->clienttreeWidget->indexOfTopLevelItem(item));
//        delete item;
        ui->clienttreeWidget->update();
    }
}

void ClientManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->clienttreeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void ClientManagerForm::on_searchPushButton_clicked()
{
    ui->searchTreeWidget->clear();
//    for(int i = 0; i < ui->treeWidget->columnCount(); i++)
    int i = ui->searchComboBox->currentIndex();
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    {
        auto items = ui->clienttreeWidget->findItems(ui->searchLineEdit->text(), flag, i);

        foreach(auto i, items) {
            ClientItem* c = static_cast<ClientItem*>(i);
            int id = c->id();
            QString name = c->getName();
            QString number = c->getPhoneNumber();
            QString address = c->getAddress();
            ClientItem* item = new ClientItem(id, name, number, address);
            ui->searchTreeWidget->addTopLevelItem(item);
        }
    }
}

void ClientManagerForm::on_modifyPushButton_clicked()
{
    QTreeWidgetItem* item = ui->clienttreeWidget->currentItem();
    if(item != nullptr) {
        int key = item->text(0).toInt();
        ClientItem* c = clientList[key];
        QString name, number, address;
        name = ui->nameLineEdit->text();
        number = ui->phoneNumberLineEdit->text();
        address = ui->addressLineEdit->text();
        c->setName(name);
        c->setPhoneNumber(number);
        c->setAddress(address);
        clientList[key] = c;
    }
}

void ClientManagerForm::on_addPushButton_clicked()
{
    QString name, number, address;
    int id = makeId( );
    name = ui->nameLineEdit->text();
    number = ui->phoneNumberLineEdit->text();
    address = ui->addressLineEdit->text();
    if(name.length()) {
        ClientItem* c = new ClientItem(id, name, number, address);
        clientList.insert(id, c);
        ui->clienttreeWidget->addTopLevelItem(c);
        emit clientAdded(name);
    }
}

void ClientManagerForm::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->idLineEdit->setText(item->text(0));
    ui->nameLineEdit->setText(item->text(1));
    ui->phoneNumberLineEdit->setText(item->text(2));
    ui->addressLineEdit->setText(item->text(3));
    ui->toolBox->setCurrentIndex(0);
}

void ClientManagerForm::on_searchTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->idLineEdit->setText(item->text(0));
    ui->nameLineEdit->setText(item->text(1));
    ui->phoneNumberLineEdit->setText(item->text(2));
    ui->addressLineEdit->setText(item->text(3));
    ui->toolBox->setCurrentIndex(0);
}

void ClientManagerForm::on_deletePushButton_clicked()
{
    removeItem();
}

void ClientManagerForm::clientIdListData(int index)
{
    ui->searchTreeWidget->clear();
    qDebug("%d",index);
//    for(int i = 0; i < ui->treeWidget->columnCount(); i++)
    QTreeWidgetItem* row = new QTreeWidgetItem(ui->clienttreeWidget);
    QWidget* IdItemList = ui->clienttreeWidget->itemWidget(row,0);
    QString IdList;
    qDebug("%d",index);
    for(int i=0;i<5;i++){
        IdList.append(QString::number(i));
    }
//    for(int i = 0; i < ui->clienttreeWidget->columnCount(); i++){
//        IdItemList->
//    }
//    //auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains:Qt::MatchCaseSensitive;
//    {
//        //auto items = ui->clienttreeWidget->findItems(ui->searchLineEdit->text(), flag, i);

//        foreach(auto i) {
//            ClientItem* c = static_cast<ClientItem*>(i);
//            int id = c->id();
//            QString name = c->getName();
//            QString number = c->getPhoneNumber();
//            QString address = c->getAddress();
//            ClientItem* item = new ClientItem(id, name, number, address);
//            ui->searchTreeWidget->addTopLevelItem(item);
//        }
//    }

//    //auto items = ui->clienttreeWidget->findItems(QString::number(id),Qt::MatchContains | Qt::MatchCaseSensitive,0);
//    auto items = ui->clienttreeWidget->
//    //QTreeWidgetItem* row = new QTreeWidgetItem(ui->clienttreeWidget);
//    auto items = ui->clienttreeWidget->topLevelItem(0);

//    QList<QString> IdList;

//    foreach(auto i, items) {
//        ClientItem* c = static_cast<ClientItem*>(i);
//        int cid = c->id();
//        QString name = c->getName();
//        QString number = c->getPhoneNumber();
//        QString address = c->getAddress();
//        ClientItem* item = new ClientItem(cid, name, number, address);
//        IdList.append(QString::number(item->id()));
//    }
    qDebug("%d",2);
    emit clientDataListSent(IdList);
    qDebug("%d",3);
}

void ClientManagerForm::clientIdDataRecv(int id,QTreeWidgetItem* row)
{
    Q_UNUSED(row);

    auto items = ui->clienttreeWidget->findItems(QString::number(id),Qt::MatchContains | Qt::MatchCaseSensitive,0);

    foreach(auto i, items) {
        ClientItem* c = static_cast<ClientItem*>(i);
        QString name = c->getName();
        QString number = c->getPhoneNumber();
        QString address = c->getAddress();
        ClientItem* client = new ClientItem(id, name, number, address);
        emit clientIdDataSent(client,row);
    }
}
