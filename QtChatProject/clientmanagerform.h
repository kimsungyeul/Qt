#ifndef CLIENTMANAGERFORM_H
#define CLIENTMANAGERFORM_H

#include <QWidget>
#include <QHash>

#include "clientitem.h"

class ClientItem;
class QMenu;
class QTreeWidgetItem;

namespace Ui {
class ClientManagerForm;
}

class ClientManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ClientManagerForm(QWidget *parent = nullptr);
    ~ClientManagerForm();
    void loadData();

public slots:
    void clientIdListData(int);
    void clientNameListData(QString);
    void clientItemRecv(int);

private slots:
    /* QTreeWidget을 위한 슬롯 */
    void showContextMenu(const QPoint &);
    void removeItem();              /* QAction을 위한 슬롯 */
    void on_addPushButton_clicked();
    void on_modifyPushButton_clicked();
    void on_searchPushButton_clicked();
    void on_deletePushButton_clicked();

    void on_searchTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_clienttreeWidget_itemClicked(QTreeWidgetItem *item, int column);

signals:
    void clientAdded(int,QString);

    void clientDataListSent(QList<QString>);
    void clientFindDataSent(ClientItem*);
    void clientIdDataSent(ClientItem*);
    //void clientDatatoServerSent(int, QString);
private:
    int makeId();

    QMap<int, ClientItem*> clientList;
    Ui::ClientManagerForm *ui;
    QMenu* menu;
};

#endif // CLIENTMANAGERFORM_H
