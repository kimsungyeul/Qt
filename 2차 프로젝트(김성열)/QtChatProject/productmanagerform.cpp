#include "productmanagerform.h"
#include "productitem.h"
#include "ui_productmanagerform.h"

#include <QFile>
#include <QMenu>

ProductManagerForm::ProductManagerForm(QWidget *parent) :                           // ProductManagerForm 생성자
    QWidget(parent),
    ui(new Ui::ProductManagerForm)
{
    ui->setupUi(this);

    QList<int> sizes;                                                               // TreeWidget과 ToolBox간 거리 조절용
    sizes << 320 << 600;                                                            // 사이즈 지정
    ui->splitter->setSizes(sizes);                                                  // 사이즈 세팅

    QAction* removeAction = new QAction(tr("&Remove"));                             // Remove Action 생성
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));                 // Remove Action 동작시 removeItem슬롯 실행

    menu = new QMenu;                                                               // Action을 동작하기위한 메뉴생성 멤버변수
    menu->addAction(removeAction);                                                  // 액션 추가
    ui->producttreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);             // 위젯의 ContextMenu의 속성을 표시하기 위함
    connect(ui->producttreeWidget, SIGNAL(customContextMenuRequested(QPoint)),      // producttreeWidget내부에서 우클릭동작시 ContextMenu를 실행하기 위함
            this, SLOT(showContextMenu(QPoint)));

    connect(ui->searchLineEdit, SIGNAL(returnPressed()),                            // searchLineEdit의 returnPressed동작시 searchPushButton슬롯 실행
            this, SLOT(on_searchPushButton_clicked()));
}

ProductManagerForm::~ProductManagerForm()                                           // ProductManagerForm 소멸자
{
    delete ui;                                                                      // ui 종료

    QFile file("productlist.txt");                                                  // 파일명 설정
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))                         // 파일저장이 안된다면 리턴
        return;

    QTextStream out(&file);                                                         // 파일출력용 스트림 생성
    for (const auto& v : productList) {                                             // productList데이터를 저장 반복
        ProductItem* p = v;                                                         // productList의 항목을 각각 p에 저장
        out << p->pid() << ", " << p->getPName() << ", ";                           // pid, pname, price, stock형으로 저장후 다시 반복
        out << p->getPrice() << ", ";
        out << p->getStock() << "\n";
    }
    file.close( );                                                                  // 파일 Close
}

void ProductManagerForm::loadData()                                                 // 프로그램실행시 productList데이터 불러오기
{
    QFile file("productlist.txt");                                                  // 불러올파일명 설정
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))                          // 파일이 열리지 않는다면 리턴
        return;

    QTextStream in(&file);                                                          // 파일스트림 생성
    while (!in.atEnd()) {                                                           // 스트림데이터가끝날때까지 반복
        QString line = in.readLine();                                               // 스트림데이터를 읽어 저장할 QString 생성
        QList<QString> row = line.split(", ");                                      // ', ' 문자가 끝날떄마다 잘라서 QList에 저장
        if(row.size()) {                                                            // 문자가 잘려져 하나의 item이 만들어진다면
            int pid = row[0].toInt();                                               // 0번쨰항목 pid로 저장
            int price = row[2].toInt();                                             // 2번쨰항목 price로 저장
            int stock = row[3].toInt();                                             // 3번쨰항목 stock로 저장
            ProductItem* p = new ProductItem(pid, row[1], price, stock);            // pid및 1,2,3번항목을 item으로 저장
            ui->producttreeWidget->addTopLevelItem(p);                              // producttreeWidget에 항목 추가
            productList.insert(pid, p);                                             // productList에 항목추가
        }
    }
    file.close( );                                                                  // 파일 Close
}

int ProductManagerForm::makePId( )                                                  // Product Id를 부여하기위한 멤버함수
{
    if(productList.size( ) == 0) {                                                  // productList의 데이터가 없다면
        return 8000;                                                                // id를 8000번부터 부여
    } else {
        auto id = productList.lastKey();                                            // productList의 마지막값을 id로 가져와
        return ++id;                                                                // +1 하여 아이디 부여
    }
}

void ProductManagerForm::removeItem()                                               // treewidget의 항목 제거용
{
    QTreeWidgetItem* item = ui->producttreeWidget->currentItem();                   // 선택된 항목을 저장
    if(item != nullptr) {                                                           // 항목이 비어있지 않다면
        productList.remove(item->text(0).toInt());                                  // item의 0번쨰인 Key(pid)를 제거
        ui->producttreeWidget->takeTopLevelItem(ui->producttreeWidget               // producttreeWidget 의 선택된 항목제거
                                                ->indexOfTopLevelItem(item));
        ui->producttreeWidget->update();                                            // producttreeWidget 업데이트
    }
}

void ProductManagerForm::showContextMenu(const QPoint &pos)                         // treewidget내에서 우클릭시 action을 사용하기 위함
{
    QPoint globalPos = ui->producttreeWidget->mapToGlobal(pos);                     // 우클릭된 모니터의 좌표값 불러오기
    menu->exec(globalPos);                                                          // 좌표값기준으로 menu 실행
}

void ProductManagerForm::on_searchPushButton_clicked()                              // Search버튼 - Item검색
{
    ui->searchTreeWidget->clear();                                                  // searchTreeWidget 업데이트
    int i = ui->searchComboBox->currentIndex();                                     // comboBox의 최신값 저장
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains                       // flag 세부사항 설정
                   : Qt::MatchCaseSensitive;
    {
        auto items = ui->producttreeWidget->findItems(ui->searchLineEdit            // flag에 맞도록 searchLineEdit의 항목을 찾아 item저장
                                                      ->text(), flag, i);

        foreach(auto i, items) {                                                    // 찾은 item항목의 내부값들을 저장
            ProductItem* p = static_cast<ProductItem*>(i);                          // 최신선택항목 item값 저장
            int pid = p->pid();                                                     // 내부객체에서 pid얻기
            QString pname = p->getPName();                                          // 내부객체에서 pname얻기
            int price = p->getPrice();                                              // 내부객체에서 price얻기
            int stock = p->getStock();                                              // 내부객체에서 stock얻기
            ProductItem* item = new ProductItem(pid, pname, price, stock);          // 뽑아저 저장한 항목들을 새로운 아이템으로 저장
            ui->searchTreeWidget->addTopLevelItem(item);                            // searchTreeWidget에 항목으로 추가
        }
    }
}

void ProductManagerForm::on_modifyPushButton_clicked()                              // Modify버튼 - Item수정
{
    QTreeWidgetItem* item = ui->producttreeWidget->currentItem();                   // producttreeWidget에서 최신선택항목 가져오기
    if(item != nullptr) {                                                           // item항목이 비어있지않다면
        int key = item->text(0).toInt();                                            // 0번째항목에서 key값추출
        ProductItem* p = productList[key];                                          // productList에 key값을 이용해 아이템 추출
        QString pname;                                                              // pname변수생성
        int price;                                                                  // price변수생성
        int stock;                                                                  // stock변수생성
        pname = ui->pnameLineEdit->text();                                          // pnameLineEdit의 text를 pname변수에 저장
        price = ui->priceLineEdit->text().toInt();                                  // priceLineEdit의 text를 price변수에 저장
        stock = ui->stockLineEdit->text().toUInt();                                 // stockLineEdit의 text를 stock변수에 저장
        p->setPName(pname);                                                         // item에 pname멤버변수저장
        p->setPrice(price);                                                         // item에 price멤버변수저장
        p->setStock(stock);                                                         // item에 stock멤버변수저장
        productList[key] = p;                                                       // productList의 key값에 item인 p 저장
    }
}


void ProductManagerForm::on_addPushButton_clicked()                                 // Add버튼 - Item추가
{
    QString pname;                                                                  // pname변수생성
    int price,stock;                                                                // price, stock변수생성

    int pid = makePId( );                                                           // id생성후 pid변수에 저장
    pname = ui->pnameLineEdit->text();                                              // pnameLineEdit의 text를 pname변수에 저장
    price = ui->priceLineEdit->text().toInt();                                      // priceLineEdit의 text를 price변수에 저장
    stock = ui->stockLineEdit->text().toUInt();                                     // stockLineEdit의 text를 stock변수에 저장
    if(pname.length()) {                                                            // 이름변수가 존재하면
        ProductItem* p = new ProductItem(pid, pname, price, stock);                 // 뽑아서 저장한 항목들을 새로운 아이템으로 저장
        productList.insert(pid, p);                                                 // productList에 id값에대한 item항목을 저장
        ui->producttreeWidget->addTopLevelItem(p);                                  // producttreeWidget에 항목으로 추가
    }
}

void ProductManagerForm::on_producttreeWidget_itemClicked(QTreeWidgetItem *item,    // TreeWidget의고객창 선택버튼 - 제품메뉴로 선택됨
                                                          int column)
{
    Q_UNUSED(column);                                                               // column인자 사용안함
    ui->idLineEdit->setText(item->text(0));                                         // idLineEdit에 item의 text(0)값을 저장
    ui->pnameLineEdit->setText(item->text(1));                                      // pnameLineEdit item의 text(1)값을 저장
    ui->priceLineEdit->setText(item->text(2));                                      // priceLineEdit item의 text(2)값을 저장
    ui->stockLineEdit->setText(item->text(3));                                      // stockLineEdit item의 text(3)값을 저장
    ui->toolBox->setCurrentIndex(0);                                                // toolbox화면상태 0번으로 변경
}

void ProductManagerForm::on_searchTreeWidget_itemClicked(QTreeWidgetItem *item,     // TreeWidget의검색창 선택버튼 - 검색메뉴로 선택됨
                                                         int column)
{
    Q_UNUSED(column);                                                               // column인자 사용안함
    ui->idLineEdit->setText(item->text(0));                                         // idLineEdit에 item의 text(0)값을 저장
    ui->pnameLineEdit->setText(item->text(1));                                      // pnameLineEdit에 item의 text(1)값을 저장
    ui->priceLineEdit->setText(item->text(2));                                      // priceLineEdit에 item의 text(2)값을 저장
    ui->stockLineEdit->setText(item->text(3));                                      // stockLineEdit에 item의 text(3)값을 저장
    ui->toolBox->setCurrentIndex(0);                                                // toolbox화면상태 0번으로 변경
}


void ProductManagerForm::on_deletePushButton_clicked()                              // Delete버튼 - Item삭제
{
    removeItem();                                                                   // removeItem() 멤버함수 호출
}

void ProductManagerForm::productIdListData(int index)                               // ProductComboBox의 Index에 따른 productList를 가져오기 위함
{
    ui->searchTreeWidget->clear();                                                  // searchTreeWidget 항목클리어
    QString PIdstr;                                                                 // PId와 제품이름을 QString형으로 같이 저장하기위한 변수
    QList<QString> PIdList;                                                         // Idstr인 QString을 저장하기위한 QList 변수

    int sentpid;                                                                    // sentpid 변수생성
    QString sentpname;                                                              // snetpname 변수생성

    for (const auto& v : productList) {                                             // productList에 모든 항목들을 반복
        ProductItem* p = v;                                                         // 뽑은 아이템을 ProductItem변수에 저장
        sentpid = p->pid();                                                         // 뽑은 pid값을 sentpid값변수에 저장
        sentpname = p->getPName();                                                  // 뽑은 pname값을 sentname값변수에 저장

        PIdstr = QString("%1, %2").arg(sentpid).arg(sentpname);                     // "PID, 제품이름" 형태의 QString형 변수 저장
        PIdList.append(PIdstr);                                                     // QList에 위에서 계산된 QString 항목 저장
    }

    emit productDataListSent(PIdList);                                              // productList를 OrderForm에 전달하기위한 시그널
}

void ProductManagerForm::productNameListData(QString pname)                         // ProductComboBox의 name설정시 이름에따른 productList를 가져오기 위함
{
    ui->searchTreeWidget->clear();                                                  // searchTreeWidget 항목클리어

    auto items = ui->producttreeWidget                                              // producttreeWidget에 name값 찾기
            ->findItems(pname,Qt::MatchCaseSensitive|Qt::MatchContains,1);

    foreach(auto i, items) {                                                        // 항목 iterater
        ProductItem* p = static_cast<ProductItem*>(i);                              // 찾은 선택항목 item값 저장
        int pid = p->pid();                                                         // 내부값에서 pid얻기
        QString pname = p->getPName();                                              // 내부값에서 pname얻기
        int price = p->getPrice();                                                  // 내부값에서 price얻기
        int stock = p->getStock();                                                  // 내부값에서 stock얻기
        ProductItem* item = new ProductItem(pid, pname, price, stock);              // 뽑아저 저장한 항목들을 새로운 아이템으로 저장
        emit productFindDataSent(item);                                             // 데이터를 뽑아 저장된 Item항목을 Order로 보내기위한 시그널
    }
}

void ProductManagerForm::productItemRecv(int pid)                                   // ProductId를 받아 productList의 item값을 추출하기위한 슬롯
{
    ProductItem* productData = productList[pid];                                    // pid에맞는 item을 변수에저장

    emit productIdDataSent(productData);                                            // pid맞는 Item을 보내는 시그널
}

void ProductManagerForm::productStockUp(int pid,int amount)                         // OrderManagerForm에서 변경된 Stock의 pid와 amount를 받아 stock을 update하기위한 슬롯
{
    ProductItem* productData = productList[pid];                                    // productList에서 pid에맞는 Item추출
    int updateStock = productData->getStock() - amount;                             // item의 stock을 가져와 구매한 양을 빼서 변수에저장
    productData->setStock(updateStock);                                             // stock값 최신화
}
