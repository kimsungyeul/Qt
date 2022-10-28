#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "clientmanagerform.h"
#include "productmanagerform.h"
#include "ordermanagerform.h"
#include "chatserver.h"

MainWindow::MainWindow(QWidget *parent)                                 // MainWindow 생성자
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    clientForm = new ClientManagerForm(this);                           // ClientManagerForm 객체생성후 부모를 MainWindow로 지정
    clientForm->setWindowTitle(tr("Client Info"));                      // 객체 Ui의 타이틀을 Client Info로 지정
    connect(clientForm, SIGNAL(destroyed()),                            // clientForm의 객체소멸시그널을 객체 Ui 삭제 시그널이이 올때까지 대기
            clientForm, SLOT(deleteLater()));

    productForm = new ProductManagerForm(this);                         // ProductManagerForm 객체생성후 부모를 MainWindow로 지정
    productForm->setWindowTitle(tr("Product Info"));                    // 객체 Ui의 타이틀을 Product Info로 지정
    connect(productForm, SIGNAL(destroyed()),                           // productForm의 객체소멸시그널을 객체 Ui 삭제 시그널이이 올때까지 대기
            productForm, SLOT(deleteLater()));

    orderForm = new OrderManagerForm(this);                             // OrderManagerForm 객체생성후 부모를 MainWindow로 지정
    orderForm->setWindowTitle(tr("Order Info"));                        // 객체 Ui의 타이틀을 Order Info로 지정
    connect(orderForm, SIGNAL(destroyed()),                             // orderForm의 객체소멸시그널을 객체 Ui 삭제 시그널이이 올때까지 대기
            orderForm, SLOT(deleteLater()));

    chatserverForm = new ChatServer(this);                              // chatserverForm 객체생성후 부모를 MainWindow로 지정
    chatserverForm->setWindowTitle(tr("ChatServer Info"));              // 객체 Ui의 타이틀을 ChatServer Info로 지정
    connect(chatserverForm, SIGNAL(destroyed()),                        // chatserverForm의 객체소멸시그널을 객체 Ui 삭제 시그널이이 올때까지 대기
            chatserverForm, SLOT(deleteLater()));

    QMdiSubWindow *cw = ui->mdiArea->addSubWindow(clientForm);          // MdiSubWindow객체로 clientForm객체 지정
    QMdiSubWindow *pw = ui->mdiArea->addSubWindow(productForm);         // MdiSubWindow객체로 productForm객체 지정
    QMdiSubWindow *ow = ui->mdiArea->addSubWindow(orderForm);           // MdiSubWindow객체로 orderForm객체 지정
    QMdiSubWindow *csw = ui->mdiArea->addSubWindow(chatserverForm);     // MdiSubWindow객체로 chatserverForm객체 지정
    ui->mdiArea->setActiveSubWindow(cw);                                // mdiArea에 SubWindow로 clientFormWindow 지정
    ui->mdiArea->setActiveSubWindow(pw);                                // mdiArea에 SubWindow로 productFormWindow 지정
    ui->mdiArea->setActiveSubWindow(ow);                                // mdiArea에 SubWindow로 orderFormWindow 지정
    ui->mdiArea->setActiveSubWindow(csw);                               // mdiArea에 SubWindow로 chatserverFormWindow 지정

    connect(orderForm, SIGNAL(clientDataSent(int)),                     // id를 받아와서 ClientManager에 원하는 인자 전해줘서 리스트 검색
            clientForm, SLOT(clientIdListData(int)));
    connect(clientForm, SIGNAL(clientDataListSent(QList<QString>)),     // ClientManagerForm에서 검색한 QList를 OrderManagerForm으로 전달
            orderForm, SLOT(clientDataListRecv(QList<QString>)));

    connect(orderForm, SIGNAL(clientDataSent(QString)),                 // name를 받아와서 ClientManager에 원하는 인자 전해줘서 리스트 검색
            clientForm, SLOT(clientNameListData(QString)));
    connect(clientForm, SIGNAL(clientFindDataSent(ClientItem*)),        // OrderManagerForm에서 선택된 리스트를 ClientManagerForm에 요청해 매칭된데이터 받기위한 connect
            orderForm, SLOT(clientFindDataRecv(ClientItem*)));

    connect(orderForm, SIGNAL(productDataSent(int)),                    // Qstring을 받아와서 ProductManager에 원하는 인자 전해줘서 리스트 검색
            productForm, SLOT(productIdListData(int)));
    connect(productForm, SIGNAL(productDataListSent(QList<QString>)),   // ProductManagerForm에서 검색한 리스트를 OrderManagerForm으로 전달
            orderForm, SLOT(productDataListRecv(QList<QString>)));

    connect(orderForm, SIGNAL(productDataSent(QString)),                // productname를 받아와서 ProductManager에 원하는 인자 전해줘서 리스트 검색
            productForm, SLOT(productNameListData(QString)));
    connect(productForm, SIGNAL(productFindDataSent(ProductItem*)),     // ProductManagerForm에서 선택된 Item을 OrderManagerForm으로 전달
            orderForm, SLOT(productFindDataRecv(ProductItem*)));

    connect(orderForm, SIGNAL(getProductItemSent(int)),                 // 선택된 ProductItem의 Product Id를 뽑아 ProductManager에서 검색
            productForm, SLOT(productItemRecv(int)));
    connect(productForm, SIGNAL(productIdDataSent(ProductItem*)),       // ProductManagerForm에서 선택된 Item을 OrderManager에 전달해 Stock,Price,Amount 최신화
            orderForm, SLOT(getProductIdDataRecv(ProductItem*)));

    connect(orderForm, SIGNAL(stockUpdate(int,int)),                    // OrderManagerForm의 Stock Update 시그널시 ProductManagerForm의 Stock Update용 connect
            productForm, SLOT(productStockUp(int,int)));


    connect(clientForm, SIGNAL(clientAdded(int, QString)),              //ClientManager에서 리스트를 읽어올때 ChatServerForm의 ClientWidget에도 출력되기 위한 connect
            chatserverForm, SLOT(addClient(int, QString)));

    clientForm->loadData();                                             // ClientManagerForm실행시 clientList데이터 불러오기용 멤버함수
    productForm->loadData();                                            // ProductManagerForm실행시 productList데이터 불러오기용 멤버함수
    orderForm->loadData();                                              // OrderManagerForm실행시 orderList데이터 불러오기용 멤버함수
}

MainWindow::~MainWindow()                                               // MainWindow 소멸자
{
    delete ui;
}

void MainWindow::on_actionClient_triggered()                            // Client Action이 trigger시 실행되는 슬롯
{
    if(clientForm != nullptr) {                                         // clientForm이 비어있지않다면
        clientForm->setFocus();                                         // clientForm으로 Window창 초점이 맞춰짐
    }
}


void MainWindow::on_actionProduct_triggered()                           // Product Action이 trigger시 실행되는 슬롯
{
    if(productForm != nullptr) {                                        // productForm이 비어있지않다면
        productForm->setFocus();                                        // productForm으로 Window창 초점이 맞춰짐
    }
}


void MainWindow::on_actionOrder_triggered()                             // Order Action이 trigger시 실행되는 슬롯
{
    if(orderForm != nullptr) {                                          // orderForm이 비어있지않다면
        orderForm->setFocus();                                          // orderForm으로 Window창 초점이 맞춰짐
    }
}

void MainWindow::on_actionServer_triggered()                            // Server Action이 trigger시 실행되는 슬롯
{
    if(chatserverForm != nullptr) {                                     // chatserverForm이 비어있지않다면
        chatserverForm->setFocus();                                     // chatserverForm으로 Window창 초점이 맞춰짐
    }
}

