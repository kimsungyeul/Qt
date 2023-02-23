#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTreeWidget treeWidget;
    treeWidget.setColumnCount(2);
    treeWidget.setHeaderLabels(QStringList() << "Col One" << "Col Two");

    for(int i=0; i<3; i++){
        QTreeWidgetItem *pItem = new QTreeWidgetItem(&treeWidget);
        pItem->setText(0, QString::number(i));
        pItem->setText(1, "Hello");
        //->treeWidget->addTopLevelItem(pItem);
        for(int j=0;j<3;j++){
            QTreeWidgetItem *itm = new QTreeWidgetItem(pItem);
            itm->setText(0, QString::number(i));
            itm->setText(1, "world");
            //pItem->addChild(itm);
        }
    }

    treeWidget.resize(250,180);
    treeWidget.show();

    return a.exec();
}
