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

void OrderManagerForm::ClientIdDataRecv(ClientItem* ClientItem,QTreeWidgetItem* row)
{
    QString name, phonnumber, address;
    int cid;
    cid = ClientItem->id();
    name = ClientItem->getName();
    phonnumber = ClientItem->getPhoneNumber();
    address = ClientItem->getAddress();
    if(cid) {
        //row->setText(1,tr(cid));
    }
}

void OrderManagerForm::on_clientcomboBox_currentIndexChanged(int index)
{
    ui->clientInfocomboBox->clear();

    if (index == 0) {
        ui->clientInfocomboBox->clear();
    }
    else if (index == 1) {

    }
    else if (index == 2) {
        qDebug("%d",index);
    }
}

