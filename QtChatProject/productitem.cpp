#include "productitem.h"

// ProductItemd에 대한 생성자
ProductItem::ProductItem(int pid, QString pname, int price, int stock)
{
    setText(0, QString::number(pid));                   // 생성자초기값 설정
    setText(1, pname);
    setText(2, QString::number(price));
    setText(3, QString::number(stock));
}

int ProductItem::pid() const                            //pid에대한 getter 생성
{
    return text(0).toInt();                             //0번째인자인 pid값 리턴
}

QString ProductItem::getPName() const                   //pname에대한 getter 생성
{
    return text(1);                                     //1번째인자인 name값 리턴
}

void ProductItem::setPName(QString& pname)              //pname에대한 setter 생성
{
    setText(1, pname);                                  //1번째인자인 pname값 설정
}

int ProductItem::getPrice() const                       //price에대한 getter 생성
{
    return text(2).toInt();                             //2번째인자인 price값 리턴
}

void ProductItem::setPrice(int price)                   //price에대한 setter 생성
{
    setText(2, QString::number(price));                 //2번째 인자에 price값 설정
}

int ProductItem::getStock() const                       //stock에대한 getter 생성
{
    return text(3).toInt();                             //3번째인자인 stock값 리턴
}

void ProductItem::setStock(int stock)                   //stock에대한 setter 생성
{
    setText(3, QString::number(stock));                 //3번째 인자에 stock값 설정
}

//연산자 오버로딩 멤버함수 생성
bool ProductItem::operator==(const ProductItem &other) const {//클래스의 첫번쨰인자와 지정한
    return (this->text(1) == other.text(1));            // 클래스의 첫번째인자가 같다면
}
