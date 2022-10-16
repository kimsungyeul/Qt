#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "clientmanagerform.h"
#include "productmanagerform.h"
#include "ordermanagerform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    clientForm = new ClientManagerForm(this);
    clientForm->setWindowTitle(tr("Client Info"));
    connect(clientForm, SIGNAL(destroyed()),
            clientForm, SLOT(deleteLater()));
    //ui->tabWidget->addTab(clientForm, "&Client Info");

    productForm = new ProductManagerForm(this);
    productForm->setWindowTitle(tr("Product Info"));
    connect(productForm, SIGNAL(destroyed()),
            productForm, SLOT(deleteLater()));

    orderForm = new OrderManagerForm(this);
    orderForm->setWindowTitle(tr("Order Info"));

    QMdiSubWindow *cw = ui->mdiArea->addSubWindow(clientForm);
    QMdiSubWindow *pw = ui->mdiArea->addSubWindow(productForm);
    QMdiSubWindow *ow = ui->mdiArea->addSubWindow(orderForm);
    ui->mdiArea->setActiveSubWindow(cw);
    ui->mdiArea->setActiveSubWindow(pw);
    ui->mdiArea->setActiveSubWindow(ow);

    //ClientManagerForm에서 검색한 리스트를 OrderManagerForm으로 전달
    connect(clientForm, SIGNAL(clientDataListSent(QString)), orderForm, SLOT(ClientDataListRecv(QString)));

    // Qstring을 받아와서 ClientManager에 원하는 인자 전해줘서 리스트 검색
    connect(orderForm, SIGNAL(ClientDataSent(int)), clientForm, SLOT(clientIdListData(int)));

    connect(orderForm,SIGNAL(ClientIdDataSent(int,QTreeWidgetItem*)),clientForm,SLOT(clientIdDataRecv(int,QTreeWidgetItem*)));
    connect(clientForm,SIGNAL(clientIdDataSent(ClientItem*,QTreeWidgetItem*)),orderForm,SLOT(ClientIdDataRecv(ClientItem*,QTreeWidgetItem*)));

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

