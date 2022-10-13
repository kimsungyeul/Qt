#include "counter.h"

Counter::Counter(QObject* parent)
    : QObject{parent}
{
}

void Counter::setValue(int value){
    if(value != m_value){
        m_value = value;
        Q_EMIT valueChanged(value);
    }
}
