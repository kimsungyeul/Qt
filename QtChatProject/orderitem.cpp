#include "orderitem.h"

OrderItem::OrderItem(int sid, int cid, QString cname, int pid, QString pname, int amount, int totprice, QString date)
{
    setText(0, QString::number(sid));
    setText(1, QString::number(cid));
    setText(2, cname);
    setText(3, QString::number(pid));
    setText(4, pname);
    setText(5, QString::number(amount));
    setText(6, QString::number(totprice));
    setText(7, date);
}

int OrderItem::getcid() const
{
    return text(1).toInt();
}

void OrderItem::setcid(int cid)
{
    setText(1, QString::number(cid));
}

QString OrderItem::getcname() const
{
    return text(2);
}

void OrderItem::setcname(QString& cname)
{
    setText(2, cname);
}

int OrderItem::getpid() const
{
    return text(3).toInt();
}

void OrderItem::setpid(int pid)
{
    setText(3, QString::number(pid));
}

QString OrderItem::getpname() const
{
    return text(4);
}

void OrderItem::setpname(QString& pname)
{
    setText(4, pname);
}

int OrderItem::getAmount() const
{
    return text(5).toInt();
}

void OrderItem::setAmount(int amount)
{
    setText(5, QString::number(amount));
}

int OrderItem::getTotPrice() const
{
    return text(6).toInt();
}

void OrderItem::setTotPrice(int totprice)
{
    setText(6, QString::number(totprice));
}

QString OrderItem::getDate() const
{
    return text(7);
}

void OrderItem::setDate(QString& date)
{
    setText(7, date);
}

int OrderItem::oid() const
{
    return text(0).toInt();
}

bool OrderItem::operator==(const OrderItem &other) const
{
    return (this->text(0) == other.text(0));
}
