#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "clientmanagerform.h"
#include "productmanagerform.h"
#include "ordermanagerform.h"
#include "chatserver.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    clientForm = new ClientManagerForm(this);
    clientForm->setWindowTitle(tr("Client Info"));
    connect(clientForm, SIGNAL(destroyed()),
            clientForm, SLOT(deleteLater()));
    //clientForm->loadData();
    //ui->tabWidget->addTab(clientForm, "&Client Info");

    productForm = new ProductManagerForm(this);
    productForm->setWindowTitle(tr("Product Info"));
    connect(productForm, SIGNAL(destroyed()),
            productForm, SLOT(deleteLater()));
    //productForm->loadData();

    orderForm = new OrderManagerForm(this);
    orderForm->setWindowTitle(tr("Order Info"));


    chatserverForm = new ChatServer(this);
    chatserverForm->setWindowTitle(tr("ChatServer Info"));

    QMdiSubWindow *cw = ui->mdiArea->addSubWindow(clientForm);
    QMdiSubWindow *pw = ui->mdiArea->addSubWindow(productForm);
    QMdiSubWindow *ow = ui->mdiArea->addSubWindow(orderForm);
    QMdiSubWindow *csw = ui->mdiArea->addSubWindow(chatserverForm);
    ui->mdiArea->setActiveSubWindow(cw);
    ui->mdiArea->setActiveSubWindow(pw);
    ui->mdiArea->setActiveSubWindow(ow);
    ui->mdiArea->setActiveSubWindow(csw);

    //ClientManagerForm에서 검색한 리스트를 OrderManagerForm으로 전달
    connect(clientForm, SIGNAL(clientDataListSent(QList<QString>)), orderForm, SLOT(clientDataListRecv(QList<QString>)));
    // Qstring을 받아와서 ClientManager에 원하는 인자 전해줘서 리스트 검색
    connect(orderForm, SIGNAL(clientDataSent(int)), clientForm, SLOT(clientIdListData(int)));

    //OrderManagerForm에서 선택된 리스트를 ClientManagerForm에 요청해 매칭된데이터 받기위한 connect
    connect(clientForm, SIGNAL(clientFindDataSent(ClientItem*)), orderForm, SLOT(clientFindDataRecv(ClientItem*)));
    connect(orderForm, SIGNAL(clientDataSent(QString)), clientForm, SLOT(clientNameListData(QString)));

    connect(orderForm, SIGNAL(getClientItemSent(int)), clientForm, SLOT(clientItemRecv(int)));
    connect(clientForm, SIGNAL(clientIdDataSent(ClientItem*)), orderForm, SLOT(getClientIdDataRecv(ClientItem*)));

    //ProductManagerForm에서 검색한 리스트를 OrderManagerForm으로 전달
    connect(productForm, SIGNAL(productDataListSent(QList<QString>)), orderForm, SLOT(productDataListRecv(QList<QString>)));
    // Qstring을 받아와서 ProductManager에 원하는 인자 전해줘서 리스트 검색
    connect(orderForm, SIGNAL(productDataSent(int)), productForm, SLOT(productIdListData(int)));

    //OrderManagerForm에서 선택된 리스트를 ProductManagerForm에 요청해 매칭된데이터 받기위한 connect
    connect(productForm, SIGNAL(productFindDataSent(ProductItem*)), orderForm, SLOT(productFindDataRecv(ProductItem*)));
    connect(orderForm, SIGNAL(productDataSent(QString)), productForm, SLOT(productNameListData(QString)));

    connect(orderForm, SIGNAL(getProductItemSent(int)), productForm, SLOT(productItemRecv(int)));
    connect(productForm, SIGNAL(productIdDataSent(ProductItem*)), orderForm, SLOT(getProductIdDataRecv(ProductItem*)));

    connect(orderForm, SIGNAL(stockUpdate(int,int)), productForm, SLOT(productStockUp(int,int)));

    //ClientManager에서 리스트를 읽어올때 ChatServerForm의 ClientWidget에도 출력되기 위한 connect
    connect(clientForm, SIGNAL(clientAdded(int, QString)), chatserverForm, SLOT(addClient(int, QString)));

    clientForm->loadData();
    productForm->loadData();
    orderForm->loadData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClient_triggered()
{
    if(clientForm != nullptr) {
        clientForm->setFocus();
    }
}


void MainWindow::on_actionProduct_triggered()
{
    if(productForm != nullptr) {
        productForm->setFocus();
    }
}


void MainWindow::on_actionOrder_triggered()
{
    if(orderForm != nullptr) {
        orderForm->setFocus();
    }
}

void MainWindow::on_actionServer_triggered()
{
    if(chatserverForm != nullptr) {
        chatserverForm->setFocus();
    }
}

