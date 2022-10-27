#ifndef CLIENTITEM_H
#define CLIENTITEM_H

#include <QTreeWidgetItem>

class ClientItem : public QTreeWidgetItem
{
public:
    // ClientItem에 대한 생성자
    explicit ClientItem(int id = 0, QString = "", QString = "", QString = "");

    int id() const;                                     //id에대한 getter 생성
    QString getName() const;                            //name에대한 getter 생성
    void setName(QString&);                             //name에대한 setter 생성
    QString getPhoneNumber() const;                     //phoneNum에대한 getter 생성
    void setPhoneNumber(QString&);                      //phoneNum에대한 setter 생성
    QString getAddress() const;                         //address에대한 getter 생성
    void setAddress(QString&);                          //address에 대한 setter 생성
    bool operator==(const ClientItem &other) const;     //연산자 오버로딩 멤버함수 생성
};

#endif // CLIENTITEM_H
