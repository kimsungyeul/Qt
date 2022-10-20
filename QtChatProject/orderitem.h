#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <QTreeWidgetItem>

class OrderItem : public QTreeWidgetItem
{
public:
    explicit OrderItem(int oid = 0, int cid = 0, int pid = 0,
                       int amount = 0, int totprice = 0, QString = "");
    int getcid() const;
    void setcid(int);
    int getpid() const;
    void setpid(int);
    int getAmount() const;
    void setAmount(int);
    int getTotPrice() const;
    void setTotPrice(int);
    QString getDate() const;
    void setDate(QString&);
    int oid() const;
    bool operator==(const OrderItem &other) const;
};

#endif // ORDERITEM_H
