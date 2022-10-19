#include "ordermanagerform.h"
#include "orderitem.h"
#include "ui_ordermanagerform.h"

#include <QFile>
#include <QMenu>

OrderManagerForm::OrderManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderManagerForm)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 320 << 600;
    ui->splitter->setSizes(sizes);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->ordertreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->ordertreeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    QFile file("orderlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    //ui->messageTreeWidget->resizeColumnToContents(i);
    //ui->clienttreeWidget->resizeColumnToContents(0);
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size()) {
            int oid = row[0].toInt();
            int cid = row[1].toInt();
            int pid = row[2].toInt();
            int amount = row[3].toInt();
            int totprice = row[4].toInt();

            OrderItem* o = new OrderItem(oid, cid, pid, amount, totprice, row[5]);
            ui->ordertreeWidget->addTopLevelItem(o);
            orderList.insert(oid, o);

            //emit orderAdded(row[1]);
        }
    }
    file.close( );
}

OrderManagerForm::~OrderManagerForm()
{
    delete ui;

    QFile file("orderlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const auto& v : orderList) {
        OrderItem* o = v;
        out << o->oid() << ", " << o->getcid() << ", ";
        out << o->getpid() << ", ";
        out << o-> getAmount()<< ", ";
        out << o->getTotPrice() << ", ";
        out << o->getDate() << "\n";
    }
    file.close( );
}

int OrderManagerForm::makeOId( )
{
    if(orderList.size( ) == 0) {
        return 5000;
    } else {
        auto id = orderList.lastKey();
        return ++id;
    }
}

void OrderManagerForm::removeItem()
{
    QTreeWidgetItem* item = ui->ordertreeWidget->currentItem();
    if(item != nullptr) {
        orderList.remove(item->text(0).toInt());
        ui->ordertreeWidget->takeTopLevelItem(ui->ordertreeWidget->indexOfTopLevelItem(item));
//        delete item;
        ui->ordertreeWidget->update();
    }
}

void OrderManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->ordertreeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void OrderManagerForm::on_clientcomboBox_currentIndexChanged(int index)
{
    ui->clientInfocomboBox->clear();

    if (index == 0) {
        ui->clientInfocomboBox->setEditable(false);
        ui->clienttreeWidget->clear();
        ui->clientInfocomboBox->clear();
    }
    else if (index == 1) {
        ui->clientInfocomboBox->setEditable(false);
        emit clientDataSent(index);
    }
    else if (index == 2) {
        ui->clientInfocomboBox->setEditable(true);
        ui->clientInfocomboBox->setMaxVisibleItems(5);
    }
}

void OrderManagerForm::on_clientInfocomboBox_textActivated(const QString &arg1)
{
    ui->clienttreeWidget->clear();

    if(ui->clientcomboBox->currentIndex() == 1){
        QList<QString> row = arg1.split(", ");
        emit clientDataSent(row[1]);
    }
    else if(ui->clientcomboBox->currentIndex() == 2){
        emit clientDataSent(arg1);
    }
}

void OrderManagerForm::clientFindDataRecv(ClientItem* item)
{
    if(item->getName().length()) {
        ui->clienttreeWidget->addTopLevelItem(item);
    }
}



void OrderManagerForm::clientDataListRecv(QList<QString> IdList)
{
    ui->clientInfocomboBox->addItems(IdList);
}

void OrderManagerForm::on_clienttreeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    QTreeWidgetItem* c = ui->clienttreeWidget->currentItem();
    if(c != nullptr) {
        ui->nameLineEdit->setText(item->text(1));
    }
}

void OrderManagerForm::on_productcomboBox_currentIndexChanged(int index)
{
    ui->productInfocomboBox->clear();

    if (index == 0) {
        ui->productInfocomboBox->setEditable(false);
        ui->producttreeWidget->clear();
        ui->productInfocomboBox->clear();
    }
    else if (index == 1) {
        ui->productInfocomboBox->setEditable(false);
        emit productDataSent(index);
    }
    else if (index == 2) {
        ui->productInfocomboBox->setEditable(true);
        ui->productInfocomboBox->setMaxVisibleItems(5);
    }
}

void OrderManagerForm::on_productInfocomboBox_textActivated(const QString &arg1)
{
    ui->producttreeWidget->clear();

    if(ui->productcomboBox->currentIndex() == 1){
        QList<QString> row = arg1.split(", ");
        emit productDataSent(row[1]);
    }
    else if(ui->productcomboBox->currentIndex() == 2){
        emit productDataSent(arg1);
    }
}

void OrderManagerForm::productFindDataRecv(ProductItem* item)
{
    if(item->getPName().length()) {
        ui->producttreeWidget->addTopLevelItem(item);
    }
}

void OrderManagerForm::productDataListRecv(QList<QString> PIdList)
{
    ui->productInfocomboBox->addItems(PIdList);
}

void OrderManagerForm::on_producttreeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    QTreeWidgetItem* p = ui->producttreeWidget->currentItem();
    if(p != nullptr) {
        ui->pnameLineEdit->setText(item->text(1));
        ui->stockLineEdit->setText(item->text(3));
    }
}

