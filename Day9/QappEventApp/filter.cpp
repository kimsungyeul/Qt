#include "filter.h"

#include <QEvent>
#include <QDebug>

Filter::Filter(QObject* parent) : QObject{parent}{
}

bool Filter::eventFilter(QObject* obj, QEvent* event){
    if(event->type() == QEvent::MouseButtonPress){
        qDebug() << "Event hijacked in filter";
        return true;
    }

    return QObject::eventFilter(obj,event);
}
