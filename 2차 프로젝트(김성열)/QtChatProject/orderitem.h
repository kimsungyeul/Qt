#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <QTreeWidgetItem>

class OrderItem : public QTreeWidgetItem
{
public:
    explicit OrderItem(int oid = 0, int cid = 0,        // OrderItem에 대한 생성자
                       QString = "", int pid = 0,
                       QString = "", int amount = 0,
                       int totprice = 0, QString = "");
    int oid() const;                                    //oid에대한 getter 생성
    int getcid() const;                                 //cid에대한 getter 생성
    void setcid(int);                                   //cid에대한 setter 생성
    QString getcname() const;                           //cname에대한 getter생성
    void setcname(QString&);                            //cname에대한 setter생성
    int getpid() const;                                 //pid에대한 getter 생성
    void setpid(int);                                   //pid에대한 setter 생성
    QString getpname() const;                           //pname에대한 setter생성
    void setpname(QString&);                            //pname에대한 getter생성
    int getAmount() const;                              //amount에대한getter생성
    void setAmount(int);                                //amount에대한setter생성
    int getTotPrice() const;                            //totprice에대한 getter생성
    void setTotPrice(int);                              //totprice에대한setter생성
    QString getDate() const;                            //date에대한getter생성
    void setDate(QString&);                             //date에대한setter생성
    bool operator==(const OrderItem &other) const;      //연산자 오버로딩 멤버함수 생성
};

#endif // ORDERITEM_H
