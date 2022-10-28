#include "clientmanagerform.h"
#include "ui_clientmanagerform.h"
#include "clientitem.h"

#include <QFile>
#include <QMenu>

//ClientManager생성자
ClientManagerForm::ClientManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManagerForm)
{
    ui->setupUi(this);

    QList<int> sizes;                                                           // TreeWidget과 ToolBox간 거리 조절용
    sizes << 320 << 600;                                                        // 사이즈 지정
    ui->splitter->setSizes(sizes);                                              // 사이즈 세팅

    QAction* removeAction = new QAction(tr("&Remove"));                         // Remove Action 생성
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));             // Remove Action 동작시 removeItem슬롯 실행

    menu = new QMenu;                                                           // Action을 동작하기위한 메뉴생성 멤버변수
    menu->addAction(removeAction);                                              // 액션 추가
    ui->clienttreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);          // 위젯의 ContextMenu의 속성을 표시하기 위함
    connect(ui->clienttreeWidget, SIGNAL(customContextMenuRequested(QPoint)),   // clienttreeWidget내부에서 우클릭동작시 ContextMenu를 실행하기 위함
            this, SLOT(showContextMenu(QPoint)));

    connect(ui->searchLineEdit, SIGNAL(returnPressed()),                        // searchLineEdit의 returnPressed동작시 searchPushButton슬롯 실행
            this, SLOT(on_searchPushButton_clicked()));
}

void ClientManagerForm::loadData()                                              // 프로그램 실행시 clientlist값을 불러오기 위함
{
    QFile file("clientlist.txt");                                               // 불러올파일명 설정
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))                      // 파일이 열리지 않는다면 리턴
        return;

    QTextStream in(&file);                                                      // 파일스트림 생성
    while (!in.atEnd()) {                                                       // 스트림데이터가끝날때까지 반복
        QString line = in.readLine();                                           // 스트림데이터를 읽어 저장할 QString 생성
        QList<QString> row = line.split(", ");                                  // ', ' 문자가 끝날떄마다 잘라서 QList에 저장
        if(row.size()) {                                                        // 문자가 잘려져 하나의 item이 만들어진다면
            int id = row[0].toInt();                                            // 0번쨰항목 id로 저장
            ClientItem* c = new ClientItem(id, row[1], row[2], row[3]);         // id및 1,2,3번항목을 item으로 저장
            ui->clienttreeWidget->addTopLevelItem(c);                           // clienttreeWidget에 항목 추가
            clientList.insert(id, c);                                           // clientList에 항목추가
            emit clientAdded(id,row[1]);                                        // Server폼의 ClientTreewidget에 저장하기위한 시그널
        }
    }
    file.close( );                                                              // 파일 Close
}

ClientManagerForm::~ClientManagerForm()                                         // ClientManagerForm 소멸자
{
    delete ui;                                                                  // ui 종료

    QFile file("clientlist.txt");                                               // 파일명 설정
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))                     // 파일저장이 안된다면 리턴
        return;

    QTextStream out(&file);                                                     // 파일출력용 스트림 생성
    for (const auto& v : clientList) {                                          // clientList데이터를 저장 반복
        ClientItem* c = v;                                                      // clientList의 항목을 각각 c에 저장
        out << c->id() << ", " << c->getName() << ", ";                         // id, name, number, address형으로 저장후 다시 반복
        out << c->getPhoneNumber() << ", ";
        out << c->getAddress() << "\n";
    }
    file.close( );                                                              // 파일 Close
}

int ClientManagerForm::makeId( )                                                // Client Id를 부여하기위한 멤버함수
{
    if(clientList.size( ) == 0) {                                               // clientList의 데이터가 없다면
        return 1000;                                                            // id를 1000번부터 부여
    } else {
        auto id = clientList.lastKey();                                         // clientList의 마지막값을 id로 가져와
        return ++id;                                                            // +1 하여 아이디 부여
    }
}

void ClientManagerForm::removeItem()                                            // treewidget의 항목 제거용
{
    QTreeWidgetItem* item = ui->clienttreeWidget->currentItem();                // 선택된 항목을 저장
    if(item != nullptr) {                                                       // 항목이 비어있지 않다면
        clientList.remove(item->text(0).toInt());                               // item의 0번쨰인 Key(id)를 제거
        ui->clienttreeWidget->takeTopLevelItem(ui->clienttreeWidget             // clienttreeWidget 의 선택된 항목제거
                                               ->indexOfTopLevelItem(item));
        ui->clienttreeWidget->update();                                         // clienttreeWidget 업데이트
    }
}

void ClientManagerForm::showContextMenu(const QPoint &pos)                      // treewidget내에서 우클릭시 action을 사용하기 위함
{
    QPoint globalPos = ui->clienttreeWidget->mapToGlobal(pos);                  // 우클릭된 모니터의 좌표값 불러오기
    menu->exec(globalPos);                                                      // 좌표값기준으로 menu 실행
}

void ClientManagerForm::on_searchPushButton_clicked()                           // Search버튼 - Item검색
{
    ui->searchTreeWidget->clear();                                              // searchTreeWidget 업데이트
//    for(int i = 0; i < ui->treeWidget->columnCount(); i++)
    int i = ui->searchComboBox->currentIndex();                                 // comboBox의 최신값 저장
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains                   // flag 세부사항 설정
                   : Qt::MatchCaseSensitive;
    {
        auto items = ui->clienttreeWidget->findItems(ui->searchLineEdit         // flag에 맞도록 searchLineEdit의 항목을 찾아 item저장
                                                     ->text(), flag, i);

        foreach(auto i, items) {                                                // 찾은 item항목의 내부값들을 저장
            ClientItem* c = static_cast<ClientItem*>(i);                        // 최신선택항목 item값 저장
            int id = c->id();                                                   // 내부값에서 id얻기
            QString name = c->getName();                                        // 내부값에서 name얻기
            QString number = c->getPhoneNumber();                               // 내부값에서 phonnumber얻기
            QString address = c->getAddress();                                  // 내부값에서 address얻기
            ClientItem* item = new ClientItem(id, name, number, address);       // 뽑아저 저장한 항목들을 새로운 아이템으로 저장
            ui->searchTreeWidget->addTopLevelItem(item);                        // searchTreeWidget에 항목으로 추가
        }
    }
}

void ClientManagerForm::on_modifyPushButton_clicked()                           // Modify버튼 - Item수정
{
    QTreeWidgetItem* item = ui->clienttreeWidget->currentItem();                // clienttreeWidget에서 최신선택항목 가져오기
    if(item != nullptr) {                                                       // item항목이 비어있지않다면
        int key = item->text(0).toInt();                                        // 0번째항목에서 key값추출
        ClientItem* c = clientList[key];                                        // clientList에 key값을 이용해 아이템 추출
        QString name, number, address;                                          // 이름,전화번호,주소 QString형 변수 생성
        name = ui->nameLineEdit->text();                                        // nameLineEdit의 text를 name변수에 저장
        number = ui->phoneNumberLineEdit->text();                               // phoneNumberLineEdit의 text를 number변수에 저장
        address = ui->addressLineEdit->text();                                  // addressLineEdit의 text를 address변수에 저장
        c->setName(name);                                                       // item에 name멤버변수저장
        c->setPhoneNumber(number);                                              // item에 number멤버변수저장
        c->setAddress(address);                                                 // item에 address멤버변수저장
        clientList[key] = c;                                                    // clientList의 key값에 item인 c 저장
    }
}

void ClientManagerForm::on_addPushButton_clicked()                              // Add버튼 - Item추가
{
    QString name, number, address;                                              // 이름,전화번호,주소 QString형 변수 생성
    int id = makeId( );                                                         // id생성후 id변수에 저장
    name = ui->nameLineEdit->text();                                            // nameLineEdit에 text를 name변수에 저장
    number = ui->phoneNumberLineEdit->text();                                   // phoneNumberLineEdit의 text를 number변수에 저장
    address = ui->addressLineEdit->text();                                      // addressLineEdit의 text를 address변수에 저장
    if(name.length()) {                                                         // 이름변수가 존재하면
        ClientItem* c = new ClientItem(id, name, number, address);              // 뽑아저 저장한 항목들을 새로운 아이템으로 저장
        clientList.insert(id, c);                                               // clientList에 id값에대한 item항목을 저장
        ui->clienttreeWidget->addTopLevelItem(c);                               // clienttreeWidget에 항목으로 추가
        emit clientAdded(id,name);                                              // Server폼의 ClientTreewidget에 저장하기위한 시그널
    }
}

void ClientManagerForm::on_clienttreeWidget_itemClicked(QTreeWidgetItem *item,  // TreeWidget의고객창 선택버튼 - 고객메뉴로 선택됨
                                                        int column)
{
    Q_UNUSED(column);                                                           // column인자 사용안함
    ui->idLineEdit->setText(item->text(0));                                     // idLineEdit에 item의 text(0)값을 저장
    ui->nameLineEdit->setText(item->text(1));                                   // nameLineEdit에 item의 text(1)값을 저장
    ui->phoneNumberLineEdit->setText(item->text(2));                            // phoneNumberLineEdit item의 text(2)값을 저장
    ui->addressLineEdit->setText(item->text(3));                                // addressLineEdit에 item의 text(3)값을 저장
    ui->toolBox->setCurrentIndex(0);                                            // toolbox화면상태 0번으로 변경
}

void ClientManagerForm::on_searchTreeWidget_itemClicked(QTreeWidgetItem *item,  // TreeWidget의검색창 선택버튼 - 검색메뉴로 선택됨
                                                        int column)
{
    Q_UNUSED(column);                                                           // column인자 사용안함
    ui->idLineEdit->setText(item->text(0));                                     // idLineEdit에 item의 text(0)값을 저장
    ui->nameLineEdit->setText(item->text(1));                                   // nameLineEdit에 item의 text(1)값을 저장
    ui->phoneNumberLineEdit->setText(item->text(2));                            // phoneNumberLineEdit item의 text(2)값을 저장
    ui->addressLineEdit->setText(item->text(3));                                // addressLineEdit에 item의 text(3)값을 저장
    ui->toolBox->setCurrentIndex(0);                                            // toolbox화면상태 0번으로 변경
}

void ClientManagerForm::on_deletePushButton_clicked()                           // Delete버튼 - Item삭제
{
    removeItem();                                                               // removeItem() 멤버함수 호출
}

void ClientManagerForm::clientIdListData(int index)                             // ClientComoboBox의 Index에 따른 ClientList를 가져오기 위함
{
    ui->searchTreeWidget->clear();                                              // searchTreeWidget 항목클리어
    QString Idstr;                                                              // Id와 이름을 QString형으로 같이 저장하기위한 변수
    QList<QString> IdList;                                                      // Idstr인 QString을 저장하기위한 QList 변수

    int sentid;                                                                 // clientList에서 찾은 항목에 id저장용 변수
    QString sentname;                                                           // clientList에서 찾은 항목에 name저장용 변수

    for (const auto& v : clientList) {                                          // clientList에 모든 항목들을 반복
        ClientItem* c = v;                                                      // 뽑은 아이템을 ClientItem변수에 저장
        sentid = c->id();                                                       // 뽑은 id값을 sentid변수에 저장
        sentname = c->getName();                                                // 뽑은 name값을 sentname값변수에 저장

        Idstr = QString("%1, %2").arg(sentid).arg(sentname);                    // "ID, 이름" 형태의 QString형 변수 저장
        IdList.append(Idstr);                                                   // QList에 위에서 계산된 QString 항목 저장
    }

    emit clientDataListSent(IdList);                                            // ClientList를 OrderForm에 전달하기위한 시그널
}

void ClientManagerForm::clientNameListData(QString name)                        // ClientComboBox의 name설정시 이름에따른 ClientList 가져오기 위함
{
    ui->searchTreeWidget->clear();                                              // searchTreeWidget 항목클리어

    auto items = ui->clienttreeWidget->findItems(name,Qt::MatchCaseSensitive    // clienttreeWidget에 name값 찾기
                                                 |Qt::MatchContains,1);

    foreach(auto i, items) {                                                    // 항목 iterater
        ClientItem* c = static_cast<ClientItem*>(i);                            // 찾은 선택항목 item값 저장
        int id = c->id();                                                       // 내부값에서 id얻기
        QString name = c->getName();                                            // 내부값에서 name얻기
        QString number = c->getPhoneNumber();                                   // 내부값에서 phonnumber얻기
        QString address = c->getAddress();                                      // 내부값에서 address얻기
        ClientItem* item = new ClientItem(id, name, number, address);           // 뽑아저 저장한 항목들을 새로운 아이템으로 저장
        emit clientFindDataSent(item);                                          // 데이터를 뽑아 저장된 Item항목을 Order로 보내기위한 시그널
    }
}
