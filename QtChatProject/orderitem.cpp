#include "orderitem.h"

OrderItem::OrderItem(int sid, int cid, int pid, int amount, int totprice, QString date)
{
    setText(0, QString::number(sid));
    setText(1, QString::number(cid));
    setText(2, QString::number(pid));
    setText(3, QString::number(amount));
    setText(4, QString::number(totprice));
    setText(5, date);
}

int OrderItem::getcid() const
{
    return text(2).toInt();
}

void OrderItem::setcid(int cid)
{
    setText(2, QString::number(cid));
}

int OrderItem::getpid() const
{
    return text(3).toInt();
}

void OrderItem::setpid(int pid)
{
    setText(3, QString::number(pid));
}

int OrderItem::getAmount() const
{
    return text(4).toInt();
}

void OrderItem::setAmount(int amount)
{
    setText(4, QString::number(amount));
}

int OrderItem::getTotPrice() const
{
    return text(5).toInt();
}

void OrderItem::setTotPrice(int totprice)
{
    setText(5, QString::number(totprice));
}

QString OrderItem::getDate() const
{
    return text(1);
}

void OrderItem::setDate(QString& date)
{
    setText(1, date);
}

int OrderItem::oid() const
{
    return text(0).toInt();
}

bool OrderItem::operator==(const OrderItem &other) const
{
    return (this->text(1) == other.text(1));
}
