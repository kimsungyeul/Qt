#ifndef ORDERMANAGERFORM_H
#define ORDERMANAGERFORM_H

#include "clientitem.h"
#include "productitem.h"
#include <QWidget>
#include <QHash>

#include "orderitem.h"

class OrderItem;                                                                // OrderItem 클래스 참조
class QMenu;                                                                    // QMenu 클래스 참조
class QTreeWidgetItem;                                                          // QTreeWidgetItem 클래스 참조
class ClientManagerForm;                                                        // ClientManagerForm 클래스 참조
class ProductManagerForm;                                                       // ProductManagerForm 클래스 참조

namespace Ui {
class OrderManagerForm;
}

class OrderManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit OrderManagerForm(QWidget *parent = nullptr);                       // OrderManagerForm 생성자
    ~OrderManagerForm();                                                        // OrderManagerForm 소멸자
    void loadData();                                                            // 프로그램실행시 orderList데이터 불러오기

public slots:

    void clientDataListRecv(QList<QString>);                                    // ClientList에서 뽑은 cid, cname의 QList형으로 받기위한 슬롯
    void clientFindDataRecv(ClientItem*);                                       // ClientItem에서 검색된 값을 받기위한 슬롯

    void productDataListRecv(QList<QString>);                                   // productList에서 뽑은 pid, pname의 QList형으로 받기위한 슬롯
    void productFindDataRecv(ProductItem*);                                     // productList에서 검색된 값을 받기위한 슬롯
    void getProductIdDataRecv(ProductItem*);                                    // stock의 값을 최신화하기위한 슬롯

private slots:
    void showContextMenu(const QPoint &);                                       // treewidget내에서 우클릭시 action을 사용하기 위함
    void removeItem();                                                          // treewidget의 항목 제거용

    void on_clientcomboBox_currentIndexChanged(int index);                      // clientcomboBox의 index변경시 실행되는 슬롯
    void on_clientInfocomboBox_textActivated(const QString &arg1);              // clientInfocomboBox의 text가 활성화시 실행되는 슬롯
    void on_clienttreeWidget_itemDoubleClicked(QTreeWidgetItem *item,           // clienttreeWidget의 항목이 클릭시 실행되는 슬롯
                                               int column);

    void on_productcomboBox_currentIndexChanged(int index);                     // productcomboBox의 index변경시 실행되는 슬롯
    void on_productInfocomboBox_textActivated(const QString &arg1);             // productInfocomboBox의 text가 활성화시 실행되는 슬롯
    void on_producttreeWidget_itemDoubleClicked(QTreeWidgetItem *item,          // producttreeWidget의 항목이 클릭시 실행되는 슬롯
                                                int column);

    void on_addpushButton_clicked();                                            // Add버튼 - Item추가
    void on_amountspinBox_valueChanged(int arg1);                               // amountspinBox버튼 - spinbox값변경
    void on_ordertreeWidget_itemClicked(QTreeWidgetItem *item, int column);     // ordertreeWidget항목 선택시 Toolbox의 LineEdit에 항목을 추가하기 위함
    void on_deletepushButton_clicked();                                         // Delete버튼 - Item삭제
    void on_modifypushButton_clicked();                                         // Modify버튼 - Item수정

signals:
    void clientDataSent(int);                                                   // clientcomboBox에서 받은 index를 clientmanager로 전달하기위한 시그널
    void clientDataSent(QString);                                               // clientcomboBox에서 받은 name를 clientmanager로 전달하기위한 시그널

    void productDataSent(int);                                                  // productcomboBox에서 받은 index를 productmanager로 전달하기위한 시그널
    void productDataSent(QString);                                              // productcomboBox에서 받은 pname을 productmanager로 전달하기위한 시그널
    void getProductItemSent(int);                                               // productId를 productmanager에 보내 검색하기위한 시그널
    void stockUpdate(int,int);                                                  // pid와 amount를 받아 stock을 업데이트하기위한 시그널

private:
    int makeOId();                                                              // Order Id를 부여하기위한 멤버함수
    QMap<int, OrderItem*> orderList;                                            // Id값에따라 OrderItem을 Qmap으로 저장하기위함
    Ui::OrderManagerForm *ui;                                                   // Ui를 사용하기위한 멤버변수
    QMenu* menu;                                                                // Action을 동작하기위한 메뉴생성 멤버변수
};

#endif // ORDERMANAGERFORM_H
