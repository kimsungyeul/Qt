#include "clientitem.h"

// ClientItem에 대한 생성자
ClientItem::ClientItem(int id, QString name,
                       QString phoneNumber, QString address)
{
    setText(0, QString::number(id));                    // 생성자초기값 설정
    setText(1, name);
    setText(2, phoneNumber);
    setText(3, address);
}

int ClientItem::id() const                              //id에대한 getter 생성
{
    return text(0).toInt();                             //0번째인자인 id값 리턴
}

QString ClientItem::getName() const                     //name에대한 getter 생성
{
    return text(1);                                     //1번째인자인 name값 리턴
}

void ClientItem::setName(QString& name)                 //name에대한 setter 생성
{
    setText(1, name);                                   //1번째인자인 name값 설정
}

QString ClientItem::getPhoneNumber() const              //phoneNum에대한 getter 생성
{
    return text(2);                                     //2번째인자인 phoneNum값 리턴
}

void ClientItem::setPhoneNumber(QString& phoneNumber)   //phonNum에대한 setter 생성
{
    setText(2, phoneNumber);                            //2번째 인자에 phonNum값 설정
}

QString ClientItem::getAddress() const                  //address에대한 getter 생성
{
    return text(3);                                     //3번째인자인 addrees값 리턴
}

void ClientItem::setAddress(QString& address)           //address에 대한 setter 생성
{
    setText(3, address);                                //3번째 인자에 address값 설정
}

//연산자 오버로딩 멤버함수 생성
bool ClientItem::operator==(const ClientItem &other) const {//클래스의 첫번쨰인자와 지정한
    return (this->text(1) == other.text(1));                // 클래스의 첫번째인자가 같다면
}
