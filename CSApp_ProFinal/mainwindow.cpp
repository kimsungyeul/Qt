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
    //    ClientManagerForm *clientForm1 = new ClientManagerForm(0);
    //    clientForm1->show();
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

