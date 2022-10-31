#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include <QTreeWidgetItem>

class ProductItem : public QTreeWidgetItem
{
public:
    // ProducItem에 대한 생성자
    explicit ProductItem(int pid = 0, QString = "", int price = 0, int stock = 0);

    int pid() const;                                    //pid에대한 getter 생성
    QString getPName() const;                           //pname에대한 getter 생성
    void setPName(QString&);                            //pname에대한 setter 생성
    int getPrice() const;                               //price에대한 getter 생성
    void setPrice(int);                                 //price에대한 setter 생성
    int getStock() const;                               //stock에대한 getter 생성
    void setStock(int);                                 //stock에대한 setter 생성
    bool operator==(const ProductItem &other) const;    //연산자 오버로딩 멤버함수 생성
};

#endif // PRODUCTITEM_H
