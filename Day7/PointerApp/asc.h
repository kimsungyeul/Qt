#ifndef ASC_H
#define ASC_H

#if 1
// QSharedPointer 클래스
#include "object.h"

#include <QObject>
#include <QSharedPointer>

class Consumer : public QObject{
public:
    explicit Consumer(QObject* parent = nullptr);
    ~Consumer();

    QSharedPointer<Object> objector;
};

#endif

#endif // ASC_H
