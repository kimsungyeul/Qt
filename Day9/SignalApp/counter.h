#ifndef COUNTER_H
#define COUNTER_H


#include <QDebug>

#include<QObject.h>

class QVariant;

class Counter : public QObject{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
public:
    explicit Counter(QObject* parent = nullptr);
    int value() const{
        return m_value;
    }
public Q_SLOTS:
    void setValue(int value);

Q_SIGNALS:
    void valueChanged(int newValue);

private:
    int m_value;
};

#endif // COUNTER_H
