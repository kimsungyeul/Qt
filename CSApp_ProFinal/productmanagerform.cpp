#include "productmanagerform.h"
#include "productitem.h"
#include "ui_productmanagerform.h"

#include <QFile>
#include <QMenu>

ProductManagerForm::ProductManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductManagerForm)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 320 << 600;
    ui->splitter->setSizes(sizes);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->producttreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->producttreeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));

    QFile file("productlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size()) {
            int pid = row[0].toInt();
            int price = row[2].toInt();
            int stock = row[3].toInt();
            ProductItem* p = new ProductItem(pid, row[1], price, stock);
            ui->producttreeWidget->addTopLevelItem(p);
            productList.insert(pid, p);

            emit productAdded(row[1]);
        }
    }
    file.close( );

//    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
//    item->setText(0, "100");
//    item->setText(1, "원주연");
//    item->setText(2, "010-1234-4567");
//    item->setText(3, "대한민국");

}

ProductManagerForm::~ProductManagerForm()
{
    delete ui;

    QFile file("productlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const auto& v : productList) {
        ProductItem* p = v;
        out << p->pid() << ", " << p->getPName() << ", ";
        out << p->getPrice() << ", ";
        out << p->getStock() << "\n";
    }
    file.close( );
}

int ProductManagerForm::makePId( )
{
    if(productList.size( ) == 0) {
        return 0;
    } else {
        auto id = productList.lastKey();
        return ++id;
    }
}

void ProductManagerForm::removeItem()
{
    QTreeWidgetItem* item = ui->producttreeWidget->currentItem();
    if(item != nullptr) {
        productList.remove(item->text(0).toInt());
        ui->producttreeWidget->takeTopLevelItem(ui->producttreeWidget->indexOfTopLevelItem(item));
//        delete item;
        ui->producttreeWidget->update();
    }
}

void ProductManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->producttreeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void ProductManagerForm::on_searchPushButton_clicked()
{
    ui->searchTreeWidget->clear();
//    for(int i = 0; i < ui->treeWidget->columnCount(); i++)
    int i = ui->searchComboBox->currentIndex();
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    {
        auto items = ui->producttreeWidget->findItems(ui->searchLineEdit->text(), flag, i);

        foreach(auto i, items) {
            ProductItem* p = static_cast<ProductItem*>(i);
            int pid = p->pid();
            QString pname = p->getPName();
            int price = p->getPrice();
            int stock = p->getStock();
            ProductItem* item = new ProductItem(pid, pname, price, stock);
            ui->searchTreeWidget->addTopLevelItem(item);
        }
    }
}

void ProductManagerForm::on_modifyPushButton_clicked()
{
    QTreeWidgetItem* item = ui->producttreeWidget->currentItem();
    if(item != nullptr) {
        int key = item->text(0).toInt();
        ProductItem* p = productList[key];
        QString pname;
        int price;
        int stock;
        pname = ui->pnameLineEdit->text();
        price = ui->priceLineEdit->text().toInt();
        stock = ui->stockLineEdit->text().toUInt();
        p->setPName(pname);
        p->setPrice(price);
        p->setStock(stock);
        productList[key] = p;
    }
}


void ProductManagerForm::on_addPushButton_clicked()
{
    QString pname;
    int price,stock;

    int pid = makePId( );
    pname = ui->pnameLineEdit->text();
    price = ui->priceLineEdit->text().toInt();
    stock = ui->stockLineEdit->text().toUInt();
    if(pname.length()) {
        ProductItem* p = new ProductItem(pid, pname, price, stock);
        productList.insert(pid, p);
        ui->producttreeWidget->addTopLevelItem(p);
        emit productAdded(pname);
    }
}

void ProductManagerForm::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->idLineEdit->setText(item->text(0));
    ui->pnameLineEdit->setText(item->text(1));
    ui->priceLineEdit->setText(item->text(2));
    ui->stockLineEdit->setText(item->text(3));
    ui->toolBox->setCurrentIndex(0);
}

void ProductManagerForm::on_searchTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->idLineEdit->setText(item->text(0));
    ui->pnameLineEdit->setText(item->text(1));
    ui->priceLineEdit->setText(item->text(2));
    ui->stockLineEdit->setText(item->text(3));
    ui->toolBox->setCurrentIndex(0);
}


void ProductManagerForm::on_deletePushButton_clicked()
{
    removeItem();
}

