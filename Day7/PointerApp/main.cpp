// 2장 마지막
#if 0
// QPointer 클래스
#include <QCoreApplication>
#include <QDebug>

#include "object.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QObject* obj1 = new QObject(nullptr);
    obj1->setObjectName("MyObject");

    QPointer<QObject> p(obj1);

    Object obj2;
    obj2.widget = p;
    obj2.useWidget();

    delete obj1;            // QPointer가 사라지므로 Nopointer출력, 주석시  .cpp에 설정된 값 출력
    obj2.useWidget();

    return a.exec();
}
#endif

#if 0
// QScopedPointer 클래스
#include "object.h"

#include <QCoreApplication>
#include <QDebug>
#include <QScopedPointer>

// The QScopedPointer class stores a pointer to a dynamically allocated object,
// and deletes it upon destruction!!
void Do(QScopedPointer<Object> &mypointer){
    qInfo() << ">>> Do" << mypointer.data();
}

void use(Object* obj){
    if(!obj){
        return;
    }
    qInfo() << ">>> Use" << obj;
}

void doStuff(){
    //Object* obj = new Object();   // dangling pointer!!
    QScopedPointer<Object> mypointer(new Object());

    use(mypointer.data());
    Do(mypointer);
}   //pointer is automatically deleted!!!

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    for(int i=0; i<10; i++) {
        qInfo() << "--------" << i;
        doStuff();
    }

    doStuff();

    return a.exec();
}
#endif

#if 0
// QSharedPointer 클래스
#include<QCoreApplication>
#include<QDebug>
#include<QSharedPointer>

#include "object.h"
#include "consumer.h"

// QSharedPointer will delete the pointer it is holding when it goes out of scope,
// provided no other QSharedPointer objects are referencing it.
void doDeleteLater(Object* obj){
    qInfo() << "Deleting: " << obj;
    obj->deleteLater();
}

QSharedPointer<Object> createPointer(){
    Object* obj = new Object();     // the bad way!!
    obj->setObjectName("Test Object");
    QSharedPointer<Object> p(obj, doDeleteLater);       // &QObject::deleteLater
    return p;
}

void doStuff(QSharedPointer<Consumer> ptr){
    qInfo() << "In function: " << ptr.data()->objector;
    ptr.clear();
}

QSharedPointer<Consumer> makeConsumer(){
    QSharedPointer<Consumer> c(new Consumer, &QObject::deleteLater);
    QSharedPointer<Object> obj = createPointer();
    //c->clear();       // 연결된 pointer가 모두 clear하면 자동 delete
    c.data()->objector.swap(obj);
    doStuff(c);

    return c;
}

int main(int argc,char* argv[]){
    QCoreApplication a(argc,argv);

    QSharedPointer<Consumer> consume = makeConsumer();
    qInfo() << "In main:" << consume.data()->objector;

    consume.clear();                // Does not actually delete!, just removes the reference

    return a.exec();
}

#endif

// 7장 Container Class
#if 0
// QVector vs QList 클래스
#include <QCoreApplication>
#include <QVector>
#include <QList>
#include <QDebug>

template<class T>
void fill(T &container){
    for(int i=0;i<5;i++){
        container.append(i);
    }
}

template<class T>
void display(T &container){
    for(int i=0;i<container.length();i++){
        if(i>0){
            auto current = reinterpret_cast<std::uintptr_t>(&container.at(i));
            auto previous = reinterpret_cast<std::uintptr_t>(&container.at(i-1));
            auto distance = current - previous;
            qInfo() << i << "At: "<<current<<"Previous: ";
            qInfo() << previous << " Distance : "<<distance;
        }
        else{
            qInfo() << i << &container.at(i) << "Distance: 0";
        }
    }
}

int main(int argc,char* argv[]){
    QCoreApplication a(argc,argv);

    QVector<int> vect = QVector<int>();
    QList<int> list = QList<int>();

    fill(vect);
    fill(list);

    qInfo() << "Int takes" << sizeof(int) << "bytes of ram";
    qInfo() << "QVector uses continuous locations in memory!";
    display(vect);
    qInfo("");
    qInfo() << "QList uses what ever it can find in memory!";
    display(list);
    qInfo("");

    return a.exec();
}
#endif

#if 0
// QSet 클래스
// 여러번 돌리면 순서가 계속바뀜(Set의 특징 - 순서가없다)
#include <QCoreApplication>
#include <QSet>
#include <QDebug>
#include <QString>

// QSet<T> is one of Qt's generic container classes.
// It stores values in an unspecified order and provides very fast lookup of the values.

int main(int argc,char* argv[]){
    QCoreApplication a(argc,argv);
    QSet<QString> people;
    people << "Bryan" << "Heather" << "Tammy" << "Chris";
    people.insert("Rango");

    //Notice this is out of order!!!
    foreach(QString person, people){
        qInfo() << person;
    }

    //Very Fast
    qInfo() << "Bryan in collection: " << people.contains("Bryan");

    return a.exec();
}
#endif

#if 0
// QHash class
#include<QCoreApplication>
#include<QHash>
#include<QDebug>

// QHash - QHash<Key,T> is one of Qt's generic container classes.
// It stores(key,value) pairs and provides very fast lookup of the value associated
// with a key.
// Works great with static info that wont change much
int main(int argc,char* argv[]){
    QCoreApplication a(argc,argv);

    QHash<QString, int> ages;
    ages.insert("Bryan",44);
    ages.insert("Tammy",49);
    ages.insert("Heather",25);
    ages.insert("Chris",27);
    ages.insert("Rango",15);

    qInfo() << "Bryan is " << ages["Bryan"] << "years old";
    qInfo() << "Keys: " << ages.keys();
    qInfo() << "Size: " << ages.size();

    foreach(QString key,ages.keys()){
        qInfo() << key << "=" << ages[key];
    }

    return a.exec();
}
#endif

#if 1
// QMap class
#include<QCoreApplication>
#include<QMap>
#include<QDebug>

// QMap - QHash<Key,T> is one of Qt's generic container classes.
// It stores(key,value) pairs and provides very fast lookup of the value associated
// with a key.
// Works great with static info that wont change much
int main(int argc,char* argv[]){
    QCoreApplication a(argc,argv);

    QMap<QString, int> ages;
    ages.insert("Bryan",44);
    ages.insert("Tammy",49);
    ages.insert("Rango",15);

    qInfo() << "Bryan is " << ages["Bryan"] << "years old";
    qInfo() << "Keys: " << ages.keys();
    qInfo() << "Size: " << ages.size();

    // Ordered, - a little slower
    foreach(QString key,ages.keys()){
        qInfo() << key << "=" << ages[key];
    }

    return a.exec();
}
#endif
