#ifndef LOGTHREAD_H
#define LOGTHREAD_H

#include <QThread>
#include <QList>

class QTreeWidgetItem;                              // QTreeWidgetItem클래스 참조

class LogThread : public QThread
{
    Q_OBJECT
public:
    explicit LogThread(QObject *parent = nullptr);  // LogThread생성자

private:
    void run();                                     // LogThread를 실행하기위한 멤버함수

    QList<QTreeWidgetItem*> itemList;               // OrderTreeWidget의 항목을 저장하기위한 멤벼변수

public slots:
    void appendData(QTreeWidgetItem*);              // server의 로그기록을 저장하기위한 슬롯
};

#endif // LOGTHREAD_H
