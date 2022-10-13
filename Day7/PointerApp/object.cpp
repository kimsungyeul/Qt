#if 0
// QPointer 클래스
#include<QDebug>

#include "object.h"

Object::Object(QObject *parent)
    : QObject(parent)
{
}

void Object::useWidget(){
    if(widget.data()){
        qInfo() << "Widget = " << widget.data();

        widget.data()->setObjectName("MyWidget");
    }
    else{
        qInfo() << "No Pointer!!";
    }
}
#endif

#if 0
// QScopedPointer 클래스
#include<QDebug>

#include "object.h"

Object::Object(QObject *parent)
    : QObject(parent)
{
    qInfo() << "Constructor" << this;
}

Object::~Object(){
    qInfo() << "Deconstructor" << this;
}

#endif

#if 0
// QSharedPointer 클래스
#include"asc.h"

#include<QDebug>

Consumer::Consumer(QObject* parent) : QObject(parent) {
    qInfo() << "Constructor" << this;
}

Consumer::~Consumer(){
    qInfo() << "Deconstructor" << this;
}

#endif
