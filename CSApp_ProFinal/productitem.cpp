#include "productitem.h"

ProductItem::ProductItem(int pid, QString pname, int price, int stock)
{
    setText(0, QString::number(pid));
    setText(1, pname);
    setText(2, QString::number(price));
    setText(3, QString::number(stock));
}

QString ProductItem::getPName() const
{
    return text(1);
}

void ProductItem::setPName(QString& pname)
{
    setText(1, pname);
}

int ProductItem::getPrice() const
{
    return text(2).toInt();
}

void ProductItem::setPrice(int price)
{
    setText(2, QString::number(price));    // c_str() --> const char*
}

int ProductItem::getStock() const
{
    return text(3).toInt();
}

void ProductItem::setStock(int stock)
{
    setText(3, QString::number(stock));
}

int ProductItem::pid() const
{
    return text(0).toInt();
}

// Define copy assignment operator.
bool ProductItem::operator==(const ProductItem &other) const {
    return (this->text(1) == other.text(1));
}
