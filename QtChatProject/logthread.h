#ifndef LOGTHREAD_H
#define LOGTHREAD_H

#include <QThread>
#include <QList>

class QTreeWidgetItem;

class LogThread : public QThread
{
    Q_OBJECT
public:
    explicit LogThread(QObject *parent = nullptr);

private:
    void run();

    QList<QTreeWidgetItem*> itemList;

signals:
    void send(int data);

public slots:
    void appendData(QTreeWidgetItem*);
};

#endif // LOGTHREAD_H
