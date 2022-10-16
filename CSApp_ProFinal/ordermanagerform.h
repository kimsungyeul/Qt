#ifndef ORDERMANAGERFORM_H
#define ORDERMANAGERFORM_H

#include "clientitem.h"
#include <QWidget>
#include <QHash>

#include "orderitem.h"

class OrderItem;
class QMenu;
class QTreeWidgetItem;
class ClientManagerForm;
class ProductManagerForm;

namespace Ui {
class OrderManagerForm;
}

class OrderManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit OrderManagerForm(QWidget *parent = nullptr);
    ~OrderManagerForm();
    void loadData();

public slots:
    void ClientIdDataRecv(ClientItem*,QTreeWidgetItem*);

    void ClientDataListRecv(QString);

private slots:
    void showContextMenu(const QPoint &);
    void removeItem();

    void on_clientcomboBox_currentIndexChanged(int index);

signals:
    void orderAdded(QString);

    void clientDataSent(int);

    void ClientIdDataSent(int,QTreeWidgetItem*);

private:
    int makeOId();

    QMap<int, OrderItem*> orderList;
    Ui::OrderManagerForm *ui;
    QMenu* menu;
};

#endif // ORDERMANAGERFORM_H
