#ifndef CLIENTMANAGERFORM_H
#define CLIENTMANAGERFORM_H

#include <QWidget>
#include <QHash>

#include "clientitem.h"

class ClientItem;                                                               // ClientItem클래스 참조
class QMenu;                                                                    // QMenu클래스 참조
class QTreeWidgetItem;                                                          // QTreeWidgetItem

namespace Ui {
class ClientManagerForm;
}

class ClientManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ClientManagerForm(QWidget *parent = nullptr);                      //ClientManagerForm 생성자
    ~ClientManagerForm();                                                       //ClientManagerForm 소멸자
    void loadData();

public slots:
    void clientIdListData(int);                                                 // ClientComoboBox의 Index에 따른 ClientList를 가져오기 위함
    void clientNameListData(QString);                                           // ClientComboBox의 name설정시 이름에따른 ClientList 가져오기 위함

private slots:
    void showContextMenu(const QPoint &);                                       // treewidget내에서 우클릭시 action을 사용하기 위함
    void removeItem();                                                          // treewidget의 항목 제거용
    void on_addPushButton_clicked();                                            // Add버튼 - Item추가
    void on_modifyPushButton_clicked();                                         // Modify버튼 - Item수정
    void on_searchPushButton_clicked();                                         // Search버튼 - Item검색
    void on_deletePushButton_clicked();                                         // Delete버튼 - Item삭제

    void on_searchTreeWidget_itemClicked(QTreeWidgetItem *item, int column);    // TreeWidget의검색창 선택버튼 - 검색메뉴로 선택됨

    void on_clienttreeWidget_itemClicked(QTreeWidgetItem *item, int column);    // TreeWidget의고객창 선택버튼 - 고객메뉴로 선택됨

signals:
    void clientAdded(int,QString);                                              // 고객을 추가하기위한 시그널

    void clientDataListSent(QList<QString>);                                    // ClientList를 OrderForm에 전달하기위한 시그널
    void clientFindDataSent(ClientItem*);                                       // Client에서 찾은 Item항목을 OrderForm으로 전달하기위한 시그널

private:
    int makeId();                                                               // Client Id를 부여하기위한 멤버함수

    QMap<int, ClientItem*> clientList;                                          // Id값에따라 CLientItem을 Qmap으로 저장하기위함
    Ui::ClientManagerForm *ui;                                                  // Ui를 사용하기위한 멤버변수
    QMenu* menu;                                                                // Action을 동작하기위한 메뉴생성 멤버변수
};

#endif // CLIENTMANAGERFORM_H
