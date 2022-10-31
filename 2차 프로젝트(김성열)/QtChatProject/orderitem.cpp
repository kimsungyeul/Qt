#include "orderitem.h"

// OrderItem에 대한 생성자
OrderItem::OrderItem(int sid, int cid, QString cname, int pid, QString pname, int amount, int totprice, QString date)
{
    setText(0, QString::number(sid));                       // 생성자초기값 설정
    setText(1, QString::number(cid));
    setText(2, cname);
    setText(3, QString::number(pid));
    setText(4, pname);
    setText(5, QString::number(amount));
    setText(6, QString::number(totprice));
    setText(7, date);
}

int OrderItem::oid() const                                  //oid에대한 getter 생성
{
    return text(0).toInt();                                 //0번째인자인 oid값 리턴
}

int OrderItem::getcid() const                               //cid에대한 getter 생성
{
    return text(1).toInt();                                 //1번째인자인 cid값 리턴
}

void OrderItem::setcid(int cid)                             //cid에대한 setter 생성
{
    setText(1, QString::number(cid));                       //1번째인자인 cid값 설정
}

QString OrderItem::getcname() const                         //cname에대한 getter생성
{
    return text(2);                                         //2번째인자인 cname값리턴
}

void OrderItem::setcname(QString& cname)                    //cname에대한 setter생성
{
    setText(2, cname);                                      //2번째 인자에 cname값설정
}

int OrderItem::getpid() const                               //pid에대한 getter 생성
{
    return text(3).toInt();                                 //3번째인자인 pid값 리턴
}

void OrderItem::setpid(int pid)                             //pid에대한 setter 생성
{
    setText(3, QString::number(pid));                       //3번째인자인 pid값 설정
}

QString OrderItem::getpname() const                         //pname에대한 setter생성
{
    return text(4);                                         //4번째인자인 pname값리턴
}

void OrderItem::setpname(QString& pname)                    //pname에대한 getter생성
{
    setText(4, pname);                                      //4번째인자인 pname값설정
}

int OrderItem::getAmount() const                            //amount에대한getter생성
{
    return text(5).toInt();                                 //5번째인자인 amount값리턴
}

void OrderItem::setAmount(int amount)                       //amount에대한setter생성
{
    setText(5, QString::number(amount));                    //5번째인자인 amount값세팅
}

int OrderItem::getTotPrice() const                      //totprice에대한 getter생성
{
    return text(6).toInt();                             //6번째인자인 totprice값리턴
}

void OrderItem::setTotPrice(int totprice)               //totprice에대한setter생성
{
    setText(6, QString::number(totprice));              //6번째인자인 totprice값세팅
}

QString OrderItem::getDate() const                          //date에대한getter생성
{
    return text(7);                                         //7번째인자인 date값리턴
}

void OrderItem::setDate(QString& date)                      //date에대한setter생성
{
    setText(7, date);                                       //7번째인자인 date값세팅
}

//연산자 오버로딩 멤버함수 생성
bool OrderItem::operator==(const OrderItem &other) const    //클래스의 첫번쨰인자와 지정한
{                                                           // 클래스의 첫번째인자가 같다면
    return (this->text(0) == other.text(0));
}
