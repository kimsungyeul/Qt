#include "ordermanagerform.h"
#include "orderitem.h"
#include "ui_ordermanagerform.h"

#include <QFile>
#include <QMenu>
#include <QDateTime>
#include <QMessageBox>

OrderManagerForm::OrderManagerForm(QWidget *parent) :                               // OrderManagerForm 생성자
    QWidget(parent),
    ui(new Ui::OrderManagerForm)
{
    ui->setupUi(this);

    QList<int> sizes;                                                               // TreeWidget과 ToolBox간 거리 조절용
    sizes << 320 << 600;                                                            // 사이즈 지정
    ui->splitter->setSizes(sizes);                                                  // 사이즈 세팅

    QAction* removeAction = new QAction(tr("&Remove"));                             // Remove Action 생성
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));                 // Remove Action 동작시 removeItem슬롯 실행

    menu = new QMenu;                                                               // Action을 동작하기위한 메뉴생성 멤버변수
    menu->addAction(removeAction);                                                  // 액션 추가
    ui->ordertreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);               // 위젯의 ContextMenu의 속성을 표시하기 위함
    connect(ui->ordertreeWidget, SIGNAL(customContextMenuRequested(QPoint)),        // ordertreeWidget내부에서 우클릭동작시 ContextMenu를 실행하기 위함
            this, SLOT(showContextMenu(QPoint)));
}

void OrderManagerForm::loadData()                                                   // 프로그램실행시 orderList데이터 불러오기
{
    QFile file("orderlist.txt");                                                    // 불러올파일명 설정
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))                          // 파일이 열리지 않는다면 리턴
        return;

    QTextStream in(&file);                                                          // 파일스트림 생성
    while (!in.atEnd()) {                                                           // 스트림데이터가끝날때까지 반복
        QString line = in.readLine();                                               // 스트림데이터를 읽어 저장할 QString 생성
        QList<QString> row = line.split(", ");                                      // ', ' 문자가 끝날떄마다 잘라서 QList에 저장
        if(row.size()) {                                                            // 문자가 잘려져 하나의 item이 만들어진다면
            int oid = row[0].toInt();                                               // 0번쨰항목 oid로 저장
            int cid = row[1].toInt();                                               // 1번쨰항목 cid로 저장
            QString cname = row[2];                                                 // 2번쨰항목 cname로 저장
            int pid = row[3].toInt();                                               // 3번쨰항목 pid로 저장
            QString pname = row[4];                                                 // 4번쨰항목 pname로 저장
            int amount = row[5].toInt();                                            // 5번쨰항목 amount로 저장
            int totprice = row[6].toInt();                                          // 6번쨰항목 totprice로 저장
            QString date = row[7];                                                  // 7번쨰항목 date로 저장

            OrderItem* o = new OrderItem(oid, cid, cname,                           // oid및 1~7번항목을 item으로 저장
                                         pid, pname, amount, totprice, date);
            orderList.insert(oid, o);                                               // orderList에 항목추가

            QTreeWidgetItem* orderitem = new QTreeWidgetItem(ui->ordertreeWidget);  // ordertreeWidget의 item객체 생성
            QString CNameIdstr, PNameIdstr;                                         // clientName, productName변수생성
            CNameIdstr = QString("%1(%2)").arg(cname).arg(cid);                     // 고객이름(고객번호) 형태의 String저장
            PNameIdstr = QString("%1(%2)").arg(pname).arg(pid);                     // 제품이름(제품번호) 형태의 String저장

            orderitem->setText(0,QString::number(oid));                             // item에 oid설정
            orderitem->setText(1, CNameIdstr);                                      // item에 고객정보설정
            orderitem->setText(2, PNameIdstr);                                      // item에 제품정보설정
            orderitem->setText(3,QString::number(amount));                          // item에 amount설정
            orderitem->setText(4,QString::number(totprice));                        // item에 totprice설정
            orderitem->setText(5,date);                                             // item에 date설정
        }
    }
    file.close( );                                                                  // 파일 Close
}

OrderManagerForm::~OrderManagerForm()                                               // ClientManagerForm 소멸자
{
    delete ui;                                                                      // ui 종료

    QFile file("orderlist.txt");                                                    // 파일명 설정
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))                         // 파일저장이 안된다면 리턴
        return;

    QTextStream out(&file);                                                         // 파일출력용 스트림 생성
    for (const auto& v : orderList) {                                               // orderList데이터를 저장 반복
        OrderItem* o = v;                                                           // orderList의 항목을 각각 o에 저장
        out << o->oid() << ", " << o->getcid() << ", " ;
        out << o->getcname() << ", " << o->getpid() << ", ";
        out << o->getpname() << ", " << o-> getAmount()<< ", ";
        out << o->getTotPrice() << ", ";
        out << o->getDate() << "\n";
    }
    file.close( );                                                                  // 파일 Close
}

int OrderManagerForm::makeOId( )                                                    // Order Id를 부여하기위한 멤버함수
{
    if(orderList.size( ) == 0) {                                                    // orderList의 데이터가 없다면
        return 5000;                                                                // id를 5000번부터 부여
    } else {
        auto oid = orderList.lastKey();                                             // orderList의 마지막값을 id로 가져와
        return ++oid;                                                               // +1 하여 아이디 부여
    }
}

void OrderManagerForm::removeItem()                                                 // treewidget의 항목 제거용
{
    QTreeWidgetItem* item = ui->ordertreeWidget->currentItem();                     // 선택된 항목을 저장
    if(item != nullptr) {                                                           // 항목이 비어있지 않다면
        orderList.remove(item->text(0).toInt());                                    // item의 0번쨰인 Key(oid)를 제거
        ui->ordertreeWidget->takeTopLevelItem(ui->ordertreeWidget                   // ordertreeWidget 의 선택된 항목제거
                                              ->indexOfTopLevelItem(item));
        ui->ordertreeWidget->update();                                              // ordertreeWidget 업데이트
    }
}

void OrderManagerForm::showContextMenu(const QPoint &pos)                           // treewidget내에서 우클릭시 action을 사용하기 위함
{
    QPoint globalPos = ui->ordertreeWidget->mapToGlobal(pos);                       // 우클릭된 모니터의 좌표값 불러오기
    menu->exec(globalPos);                                                          // 좌표값기준으로 menu 실행
}

void OrderManagerForm::on_clientcomboBox_currentIndexChanged(int index)             // clientcomboBox의 index변경시 실행되는 슬롯
{
    ui->clientInfocomboBox->clear();                                                // 현재 clientInfocomboBox 데이터 클리어

    if (index == 0) {                                                               // index가 0이라면
        ui->clientInfocomboBox->setEditable(false);                                 // clientInfocomboBox 수정불가
        ui->clienttreeWidget->clear();                                              // clienttreeWidget 클리어
        ui->clientInfocomboBox->clear();                                            // clientInfocomboBox 클리어
    }
    else if (index == 1) {                                                          // index가 1이라면
        ui->clientInfocomboBox->setEditable(false);                                 // clientInfocomboBox 수정불가
        emit clientDataSent(index);                                                 // index값을 clientmanager로 보냄
    }
    else if (index == 2) {                                                          // index가 2이라면
        ui->clientInfocomboBox->setEditable(true);                                  // clientInfocomboBox 수정가능
        ui->clientInfocomboBox->setMaxVisibleItems(5);                              // clientInfocomboBox 목록 보이는 최대갯수 5개
    }
}

void OrderManagerForm::on_clientInfocomboBox_textActivated(const QString &arg1)     // clientInfocomboBox의 text가 활성화시 실행되는 슬롯
{
    ui->clienttreeWidget->clear();                                                  // 현재 clienttreeWidget 데이터 클리어

    if(ui->clientcomboBox->currentIndex() == 1){                                    // clientcomboBox의 선택index가 1이라면
        QList<QString> row = arg1.split(", ");                                      // ", " 기준으로 잘라서 List에 담는다
        emit clientDataSent(row[1]);                                                // QList의 1번째인자(name)을 clientManager로 보냄
    }
    else if(ui->clientcomboBox->currentIndex() == 2){                               // clientcomboBox의 선택index가 2이라면
        emit clientDataSent(arg1);                                                  // text에 적혀진 이름을 clientManager로 보냄
    }
}

void OrderManagerForm::clientFindDataRecv(ClientItem* item)                         // ClientItem에서 검색된 값을 받기위한 슬롯
{
    if(item->getName().length()) {                                                  // item의 이름이 있다면
        ui->clienttreeWidget->addTopLevelItem(item);                                // clienttreeWidget에 항목추가
    }
}



void OrderManagerForm::clientDataListRecv(QList<QString> IdList)                    // ClientList에서 뽑은 cid, cname의 QList형으로 받기위한 슬롯
{
    ui->clientInfocomboBox->addItems(IdList);                                       // clientInfocomboBox에 항목추가
}

void OrderManagerForm::on_clienttreeWidget_itemDoubleClicked(QTreeWidgetItem *item, // clienttreeWidget의 항목이 클릭시 실행되는 슬롯
                                                             int column)
{
    Q_UNUSED(column);                                                               // column 사용안함

    QTreeWidgetItem* c = ui->clienttreeWidget->currentItem();                       // 선택한 item을 저장

    QString NameIdstr;                                                              // NameIdstr변수선언
    int cid = item->text(0).toInt();                                                // item의 text(0)을 cid에 저장
    QString name = item->text(1);                                                   // item의 text(1)을 name에 저장
    NameIdstr = QString("%1(%2)").arg(name).arg(cid);                               // 고객이름(고객번호) String형태로 저장


    if(c != nullptr) {                                                              // TreeWidgetItem이 비어있지않다면
        ui->nameLineEdit->setText(NameIdstr);                                       // nameLineEdit에 text저장
    }
}

void OrderManagerForm::on_productcomboBox_currentIndexChanged(int index)            // productcomboBox의 index변경시 실행되는 슬롯
{
    ui->productInfocomboBox->clear();                                               // productInfocomboBox 클리어

    if (index == 0) {                                                               // index가 0이라면
        ui->productInfocomboBox->setEditable(false);                                // productInfocomboBox 수정불가
        ui->producttreeWidget->clear();                                             // producttreeWidget 클리어
        ui->productInfocomboBox->clear();                                           // productInfocomboBox 클리어
    }
    else if (index == 1) {                                                          // index가 1이라면
        ui->productInfocomboBox->setEditable(false);                                // productInfocomboBox 수정불가
        emit productDataSent(index);                                                // index값을 productmanager로 보냄
    }
    else if (index == 2) {                                                          // index가 2이라면
        ui->productInfocomboBox->setEditable(true);                                 // productInfocomboBox 수정가능
        ui->productInfocomboBox->setMaxVisibleItems(5);                             // productInfocomboBox 목록 보이는 최대갯수 5개
    }
}

void OrderManagerForm::on_productInfocomboBox_textActivated(const QString &arg1)    // productInfocomboBox의 text가 활성화시 실행되는 슬롯
{
    ui->producttreeWidget->clear();                                                 // 현재 producttreeWidget 데이터 클리어

    if(ui->productcomboBox->currentIndex() == 1){                                   // productcomboBox의 선택index가 1이라면
        QList<QString> row = arg1.split(", ");                                      // ", " 기준으로 잘라서 List에 담는다
        emit productDataSent(row[1]);                                               // QList의 1번째인자(name)을 productManager로 보냄
    }
    else if(ui->productcomboBox->currentIndex() == 2){                              // productcomboBox의 선택index가 2이라면
        emit productDataSent(arg1);                                                 // text에 적혀진 이름을 productManager로 보냄
    }
}

void OrderManagerForm::productFindDataRecv(ProductItem* item)                       // productList에서 검색된 값을 받기위한 슬롯
{
    if(item->getPName().length()) {                                                 // item의 이름이 존재한다면
        ui->producttreeWidget->addTopLevelItem(item);                               // producttreeWidget항목에 item추가
    }
}

void OrderManagerForm::productDataListRecv(QList<QString> PIdList)                  // productList에서 뽑은 pid, pname의 QList형으로 받기위한 슬롯
{
    ui->productInfocomboBox->addItems(PIdList);                                     // productInfocomboBox에 item항목추가
}

void OrderManagerForm::on_producttreeWidget_itemDoubleClicked(QTreeWidgetItem *item,// producttreeWidget의 항목이 클릭시 실행되는 슬롯
                                                              int column)
{
    Q_UNUSED(column);                                                               // column 사용안함

    QTreeWidgetItem* p = ui->producttreeWidget->currentItem();                      // 선택한 item을 저장
    QString NameIdstr;                                                              // NameIdstr변수선언
    int pid = item->text(0).toInt();                                                // item의 text(0)을 pid에 저장
    QString pname = item->text(1);                                                  // item의 text(1)을 pname에 저장
    int stock = item->text(3).toInt();                                              // item의 text(3)을 stock에 저장
    NameIdstr = QString("%1(%2)").arg(pname).arg(pid);                              // 제품이름(제품번호) String형태로 저장

    if(p != nullptr) {                                                              // TreeWidgetItem이 비어있지않다면
        ui->pnameLineEdit->setText(NameIdstr);                                      // pnameLineEdit text저장
        ui->priceLineEdit->setText(item->text(2));                                  // priceLineEdit item->text(2)저장
        ui->stockLineEdit->setText(item->text(3));                                  // stockLineEdit item->text(3)저장
        ui->amountspinBox->setMaximum(stock);                                       // amountspinBox stock저장
    }
}

void OrderManagerForm::on_addpushButton_clicked()                                   // Add버튼 - Item추가
{
    QTreeWidgetItem* row = new QTreeWidgetItem(ui->ordertreeWidget);
    QString citemname = ui->nameLineEdit->text();
    QString pitemname = ui->pnameLineEdit->text();
    // Order Number
    if((citemname.isEmpty() != true) && (pitemname.isEmpty() != true)) {
        int oid = makeOId();
        QList<QString> clientrow = ui->nameLineEdit->text().split("(");
        QList<QString> productrow = ui->pnameLineEdit->text().split("(");
        clientrow[1] = clientrow[1].remove(QChar(')'), Qt::CaseInsensitive);
        productrow[1] = productrow[1].remove(QChar(')'), Qt::CaseInsensitive);
        // Client Name, Item Name
        int cid = clientrow[1].toInt();
        QString cname = clientrow[0];
        int pid = productrow[1].toInt();
        QString pname = productrow[0];
        int amount = ui->amountspinBox->text().toInt();
        int totprice = ui->totalpriceLineEdit->text().toInt();
        // Date
        QString date = QDateTime::currentDateTime().toString();
        OrderItem* orderitem = new OrderItem(oid, cid, cname, pid, pname,
                                             amount,totprice,date);
        orderList.insert(oid, orderitem);

        row->setText(0,QString::number(oid));
        row->setText(1,ui->nameLineEdit->text());
        row->setText(2,ui->pnameLineEdit->text());
        row->setText(3,QString::number(amount));
        row->setText(4,QString::number(totprice));
        row->setText(5,date);

        emit stockUpdate(pid,amount);
    } else {
        QMessageBox::critical(this, tr("Invalid Order"), \
                              tr("PlZ Client or Product input"));
    }
}

void OrderManagerForm::on_amountspinBox_valueChanged(int arg1)                      // amountspinBox버튼 - spinbox값변경
{
    ui->totalpriceLineEdit->setText(QString::number(arg1 * ui->priceLineEdit
                                                    ->text().toInt()));
}

void OrderManagerForm::getProductIdDataRecv(ProductItem* item)                      // stock의 값을 최신화하기위한 슬롯
{
    ui->producttreeWidget->clear();

    QString maxstock = item->text(3);
    ui->priceLineEdit->setText(item->text(2));
    ui->amountspinBox->setMaximum(maxstock.toInt());
    ui->stockLineEdit->setText(maxstock);
}

void OrderManagerForm::on_ordertreeWidget_itemClicked(QTreeWidgetItem *item,        // ordertreeWidget항목 선택시 Toolbox의 LineEdit에 항목을 추가하기 위함
                                                      int column)
{
    Q_UNUSED(column);

    QList<QString> clientrow = item->text(1).split("(");
    QList<QString> productrow = item->text(2).split("(");
    int clientID = clientrow[1].remove(QChar(')'), Qt::CaseInsensitive).toInt();
    int productID = productrow[1].remove(QChar(')'), Qt::CaseInsensitive).toInt();

    emit getProductItemSent(productID);

    ui->nameLineEdit->setText(item->text(1));
    ui->pnameLineEdit->setText(item->text(2));
    ui->totalpriceLineEdit->setText(item->text(4));
}


void OrderManagerForm::on_deletepushButton_clicked()                                // Delete버튼 - Item삭제
{
    removeItem();
}


void OrderManagerForm::on_modifypushButton_clicked()                                // Modify버튼 - Item수정
{
    QTreeWidgetItem* item = ui->ordertreeWidget->currentItem();
    if(item != nullptr) {
        int key = item->text(0).toInt();
        OrderItem* o = orderList[key];

        int befamount, afamount, totalPrice;
        QString cname,pname;

        QList<QString> productrow = ui->pnameLineEdit->text().split("(");
        productrow[1] = productrow[1].remove(QChar(')'), Qt::CaseInsensitive);
        int pid = productrow[1].toInt();

        befamount = item->text(3).toInt();
        afamount = ui->amountspinBox->value();
        totalPrice = ui->totalpriceLineEdit->text().toInt();

        item->setText(3,QString::number(afamount));
        item->setText(4,QString::number(totalPrice));
        o->setAmount(afamount);
        o->setTotPrice(totalPrice);
        orderList[key] = o;
        emit stockUpdate(pid,afamount-befamount);
    }
}

