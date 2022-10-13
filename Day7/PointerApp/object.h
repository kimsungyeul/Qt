#ifndef OBJECT_H
#define OBJECT_H

#if 0
// QPointer 클래스
#include <QObject>
#include <QPointer>

class Object : public QObject
{
public:
    explicit Object(QObject *parent = nullptr);
    void useWidget();

    QPointer<QObject> widget;
signals:

};
#endif

#if 0
// QScopedPointer,QSharedPointer 클래스
#include <QObject>

class Object : public QObject
{
public:
    explicit Object(QObject *parent = nullptr);
    ~Object();

signals:

};
#endif

#endif // OBJECT_H
