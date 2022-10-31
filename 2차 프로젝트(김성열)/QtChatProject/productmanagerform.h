#ifndef PRODUCTMANAGERFORM_H
#define PRODUCTMANAGERFORM_H

#include <QWidget>
#include <QHash>

#include "productitem.h"

class ProductItem;                                              // ProductItem클래스 참조
class QMenu;                                                    // QMenu클래스 참조
class QTreeWidgetItem;                                          // QTreeWidgetItem클래스 참조

namespace Ui {
class ProductManagerForm;
}

class ProductManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProductManagerForm(QWidget *parent = nullptr);     // ProductManagerForm 생성자
    ~ProductManagerForm();                                      // ProductManagerForm 소멸자
    void loadData();                                            // 프로그램실행시 productList데이터 불러오기
public slots:
    void productIdListData(int);                                // ProductComboBox의 Index에 따른 productList를 가져오기 위함
    void productNameListData(QString);                          // ProductComboBox의 name설정시 이름에따른 productList를 가져오기 위함
    void productItemRecv(int);                                  // ProductId를 받아 productList의 item값을 추출하기위한 슬롯
    void productStockUp(int,int);                               // OrderManagerForm에서 변경된 Stock의 pid와 amount를 받아 stock을 update하기위한 슬롯

private slots:
    void showContextMenu(const QPoint &);                       // producttreewidget내에서 우클릭시 action을 사용하기 위한 슬롯
    void removeItem();                                          // producttreewidget의 항목 제거용
    void on_searchPushButton_clicked();                         // Product Search 버튼 - Item검색
    void on_modifyPushButton_clicked();                         // Product Modify 버튼 - Item수정
    void on_addPushButton_clicked();                            // Product Add 버튼 - Item추가
    void on_deletePushButton_clicked();                         // Product Delete 버튼 - Item삭제
    void on_searchTreeWidget_itemClicked(QTreeWidgetItem *item, // searchTreeWdiget항목 선택시 Toolbox의 LineEdit에 항목을 추가하기 위함
                                         int column);
    void on_producttreeWidget_itemClicked(QTreeWidgetItem *item,// productTreeWdiget항목 선택시 Toolbox의 LineEdit에 항목을 추가하기 위함
                                          int column);

signals:
    void productDataListSent(QList<QString>);                   // ProductManagerForm에서 검색한 리스트를 OrderManagerForm으로 전달하기위한 시그널
    void productFindDataSent(ProductItem*);                     // ProductManagerForm에서 선택된 Item을 OrderManagerForm으로 전달하기 위한 시그널
    void productIdDataSent(ProductItem*);                       // ProductManagerForm에서 선택된 Item을 OrderManager에 전달해 Stock,Price,Amount 최신화 하기위한 시그널

private:
    int makePId();                                              // Product Id를 부여하기위한 멤버함수

    QMap<int, ProductItem*> productList;                        // Id값에따라 ProductItem Qmap으로 저장하기위함
    Ui::ProductManagerForm *ui;                                 // Ui를 사용하기위한 멤버변수
    QMenu* menu;                                                // Action을 동작하기위한 메뉴생성 멤버변수
};

#endif // PRODUCTMANAGERFORM_H
