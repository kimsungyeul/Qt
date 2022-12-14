#ifndef PRODUCTMANAGERFORM_H
#define PRODUCTMANAGERFORM_H

#include <QWidget>
#include <QHash>

#include "productitem.h"

class ProductItem;
class QMenu;
class QTreeWidgetItem;

namespace Ui {
class ProductManagerForm;
}

class ProductManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProductManagerForm(QWidget *parent = nullptr);
    ~ProductManagerForm();
    void loadData();
public slots:
    void productIdListData(int);
    void productNameListData(QString);

private slots:
    void showContextMenu(const QPoint &);
    void removeItem();

    void on_searchPushButton_clicked();

    void on_modifyPushButton_clicked();

    void on_addPushButton_clicked();

    void on_searchTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_deletePushButton_clicked();

    void on_producttreeWidget_itemClicked(QTreeWidgetItem *item, int column);

signals:
    void productAdded(QString);
    void productDataListSent(QList<QString>);
    void productFindDataSent(ProductItem*);
private:
    int makePId();

    QMap<int, ProductItem*> productList;
    Ui::ProductManagerForm *ui;
    QMenu* menu;
};

#endif // PRODUCTMANAGERFORM_H
