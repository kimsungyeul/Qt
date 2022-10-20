#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include <QTreeWidgetItem>

class ProductItem : public QTreeWidgetItem
{
public:
    explicit ProductItem(int pid = 0, QString = "", int price = 0, int stock = 0);

    QString getPName() const;
    void setPName(QString&);
    int getPrice() const;
    void setPrice(int);
    int getStock() const;
    void setStock(int);
    int pid() const;
    bool operator==(const ProductItem &other) const;
};

#endif // PRODUCTITEM_H
